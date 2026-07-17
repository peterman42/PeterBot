package com.peterbot.shared.presentation

import com.peterbot.shared.data.network.RobotHttpClient
import com.peterbot.shared.domain.repository.ConfigRepository
import io.ktor.client.HttpClient
import io.ktor.client.engine.mock.MockEngine
import io.ktor.client.engine.mock.respond
import io.ktor.http.HttpStatusCode
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.ExperimentalCoroutinesApi
import kotlinx.coroutines.test.UnconfinedTestDispatcher
import kotlinx.coroutines.test.advanceUntilIdle
import kotlinx.coroutines.test.resetMain
import kotlinx.coroutines.test.runTest
import kotlinx.coroutines.test.setMain
import kotlin.test.AfterTest
import kotlin.test.BeforeTest
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertTrue

@OptIn(ExperimentalCoroutinesApi::class)
class RobotViewModelTest {

    private val testDispatcher = UnconfinedTestDispatcher()

    private class FakeConfigRepository : ConfigRepository {
        var savedHost: String? = null
        var savedPort: Int? = null

        override fun getHost(): String? = savedHost
        override fun getPort(): Int? = savedPort
        override fun saveConfig(host: String, port: Int) {
            this.savedHost = host
            this.savedPort = port
        }
        override fun getBaseUrl(): String = "http://${savedHost ?: "192.168.4.1"}:${savedPort ?: 80}"
    }

    @BeforeTest
    fun setUp() {
        Dispatchers.setMain(testDispatcher)
    }

    @AfterTest
    fun tearDown() {
        Dispatchers.resetMain()
    }

    @Test
    fun testInitializationLoadsSavedConfig() {
        val configRepo = FakeConfigRepository().apply {
            savedHost = "10.0.0.5"
            savedPort = 8888
        }
        val mockEngine = MockEngine { respond("") }
        val httpClient = RobotHttpClient(HttpClient(mockEngine)) { configRepo.getBaseUrl() }

        val viewModel = RobotViewModel(configRepo, httpClient)

        assertEquals("10.0.0.5", viewModel.uiState.value.host)
        assertEquals("8888", viewModel.uiState.value.port)
        assertTrue(viewModel.uiState.value.isConfigSaved)
    }

    @Test
    fun testSaveConfigValid() {
        val configRepo = FakeConfigRepository()
        val mockEngine = MockEngine { respond("") }
        val httpClient = RobotHttpClient(HttpClient(mockEngine)) { configRepo.getBaseUrl() }

        val viewModel = RobotViewModel(configRepo, httpClient)

        viewModel.onHostChanged("192.168.1.200")
        viewModel.onPortChanged("8080")
        viewModel.saveConfig()

        assertTrue(viewModel.uiState.value.isConfigSaved)
        assertEquals("Configuration saved!", viewModel.uiState.value.statusMessage)
        assertFalse(viewModel.uiState.value.isError)
        assertEquals("192.168.1.200", configRepo.savedHost)
        assertEquals(8080, configRepo.savedPort)
    }

    @Test
    fun testSaveConfigInvalid() {
        val configRepo = FakeConfigRepository()
        val mockEngine = MockEngine { respond("") }
        val httpClient = RobotHttpClient(HttpClient(mockEngine)) { configRepo.getBaseUrl() }

        val viewModel = RobotViewModel(configRepo, httpClient)

        // Invalid port
        viewModel.onHostChanged("192.168.1.200")
        viewModel.onPortChanged("invalid_port")
        viewModel.saveConfig()

        assertFalse(viewModel.uiState.value.isConfigSaved)
        assertEquals("Invalid port number", viewModel.uiState.value.statusMessage)
        assertTrue(viewModel.uiState.value.isError)
    }

    @Test
    fun testMoveForwardCommandSuccess() = runTest {
        val configRepo = FakeConfigRepository()
        var callCount = 0
        val mockEngine = MockEngine { request ->
            callCount++
            respond("Moved", HttpStatusCode.OK)
        }
        val httpClient = RobotHttpClient(HttpClient(mockEngine)) { configRepo.getBaseUrl() }
        val viewModel = RobotViewModel(configRepo, httpClient)

        viewModel.moveForward()
        advanceUntilIdle()

        assertEquals(1, callCount)
        assertEquals("Command executed successfully", viewModel.uiState.value.statusMessage)
        assertFalse(viewModel.uiState.value.isError)
    }
}
