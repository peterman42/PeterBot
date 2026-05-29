package com.peterbot.shared.data.repository

import com.peterbot.shared.data.local.KeyValueStorage
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertNull

class ConfigRepositoryImplTest {

    private class FakeKeyValueStorage : KeyValueStorage {
        private val strings = mutableMapOf<String, String>()
        private val ints = mutableMapOf<String, Int>()

        override fun getString(key: String): String? = strings[key]

        override fun putString(key: String, value: String) {
            strings[key] = value
        }

        override fun getInt(key: String, defaultValue: Int): Int = ints[key] ?: defaultValue

        override fun putInt(key: String, value: Int) {
            ints[key] = value
        }
    }

    @Test
    fun testInitialState() {
        val storage = FakeKeyValueStorage()
        val repo = ConfigRepositoryImpl(storage)

        assertNull(repo.getHost())
        assertNull(repo.getPort())
        assertEquals("http://192.168.4.1:80", repo.getBaseUrl())
    }

    @Test
    fun testSaveAndRetrieveConfig() {
        val storage = FakeKeyValueStorage()
        val repo = ConfigRepositoryImpl(storage)

        repo.saveConfig("192.168.1.50", 8080)

        assertEquals("192.168.1.50", repo.getHost())
        assertEquals(8080, repo.getPort())
        assertEquals("http://192.168.1.50:8080", repo.getBaseUrl())
    }

    @Test
    fun testBaseUrlSanitization() {
        val storage = FakeKeyValueStorage()
        val repo = ConfigRepositoryImpl(storage)

        repo.saveConfig("http://192.168.1.50", 80)
        assertEquals("http://192.168.1.50:80", repo.getBaseUrl())

        repo.saveConfig("https://myrobot.local", 443)
        assertEquals("https://myrobot.local:443", repo.getBaseUrl())
    }
}
