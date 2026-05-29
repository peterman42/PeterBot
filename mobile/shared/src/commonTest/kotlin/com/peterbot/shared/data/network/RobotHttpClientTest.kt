package com.peterbot.shared.data.network

import io.ktor.client.HttpClient
import io.ktor.client.engine.mock.MockEngine
import io.ktor.client.engine.mock.respond
import io.ktor.http.HttpStatusCode
import io.ktor.http.headersOf
import kotlinx.coroutines.test.runTest
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertTrue

class RobotHttpClientTest {

    private val testHost = "http://192.168.1.100"

    @Test
    fun testForwardSendsCommand0() = runTest {
        var requestedUrlPath = ""
        val mockEngine = MockEngine { request ->
            requestedUrlPath = request.url.encodedPath
            respond(
                content = "Moved",
                status = HttpStatusCode.OK,
                headers = headersOf("Content-Type", "text/plain")
            )
        }
        val client = HttpClient(mockEngine)
        val robotHttpClient = RobotHttpClient(client) { testHost }

        val result = robotHttpClient.forward()

        assertTrue(result.isSuccess)
        assertEquals("/move/0", requestedUrlPath)
    }

    @Test
    fun testBackwardSendsCommand1() = runTest {
        var requestedUrlPath = ""
        val mockEngine = MockEngine { request ->
            requestedUrlPath = request.url.encodedPath
            respond(
                content = "Moved",
                status = HttpStatusCode.OK,
                headers = headersOf("Content-Type", "text/plain")
            )
        }
        val client = HttpClient(mockEngine)
        val robotHttpClient = RobotHttpClient(client) { testHost }

        val result = robotHttpClient.backward()

        assertTrue(result.isSuccess)
        assertEquals("/move/1", requestedUrlPath)
    }

    @Test
    fun testTurnRightSendsCommand2() = runTest {
        var requestedUrlPath = ""
        val mockEngine = MockEngine { request ->
            requestedUrlPath = request.url.encodedPath
            respond(
                content = "Moved",
                status = HttpStatusCode.OK,
                headers = headersOf("Content-Type", "text/plain")
            )
        }
        val client = HttpClient(mockEngine)
        val robotHttpClient = RobotHttpClient(client) { testHost }

        val result = robotHttpClient.turnRight()

        assertTrue(result.isSuccess)
        assertEquals("/move/2", requestedUrlPath)
    }

    @Test
    fun testTurnLeftSendsCommand3() = runTest {
        var requestedUrlPath = ""
        val mockEngine = MockEngine { request ->
            requestedUrlPath = request.url.encodedPath
            respond(
                content = "Moved",
                status = HttpStatusCode.OK,
                headers = headersOf("Content-Type", "text/plain")
            )
        }
        val client = HttpClient(mockEngine)
        val robotHttpClient = RobotHttpClient(client) { testHost }

        val result = robotHttpClient.turnLeft()

        assertTrue(result.isSuccess)
        assertEquals("/move/3", requestedUrlPath)
    }

    @Test
    fun testStopSendsCommand4() = runTest {
        var requestedUrlPath = ""
        val mockEngine = MockEngine { request ->
            requestedUrlPath = request.url.encodedPath
            respond(
                content = "Moved",
                status = HttpStatusCode.OK,
                headers = headersOf("Content-Type", "text/plain")
            )
        }
        val client = HttpClient(mockEngine)
        val robotHttpClient = RobotHttpClient(client) { testHost }

        val result = robotHttpClient.stop()

        assertTrue(result.isSuccess)
        assertEquals("/move/4", requestedUrlPath)
    }

    @Test
    fun testHttpErrorReturnsFailure() = runTest {
        val mockEngine = MockEngine { request ->
            respond(
                content = "Internal Server Error",
                status = HttpStatusCode.InternalServerError,
                headers = headersOf("Content-Type", "text/plain")
            )
        }
        val client = HttpClient(mockEngine)
        val robotHttpClient = RobotHttpClient(client) { testHost }

        val result = robotHttpClient.forward()

        assertTrue(result.isFailure)
        assertEquals("Server returned status: 500 Internal Server Error", result.exceptionOrNull()?.message)
    }
}
