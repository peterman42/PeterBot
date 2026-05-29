package com.peterbot.shared.data.repository

import com.peterbot.shared.data.local.KeyValueStorage
import com.peterbot.shared.domain.repository.ConfigRepository

class ConfigRepositoryImpl(
    private val storage: KeyValueStorage
) : ConfigRepository {

    override fun getHost(): String? {
        return storage.getString(KEY_HOST)
    }

    override fun getPort(): Int? {
        val port = storage.getInt(KEY_PORT, -1)
        return if (port == -1) null else port
    }

    override fun saveConfig(host: String, port: Int) {
        storage.putString(KEY_HOST, host)
        storage.putInt(KEY_PORT, port)
    }

    override fun getBaseUrl(): String {
        val host = getHost() ?: "192.168.4.1" // ESP8266 default AP address is 192.168.4.1
        val port = getPort() ?: 80
        val sanitizedHost = if (!host.startsWith("http://") && !host.startsWith("https://")) {
            "http://$host"
        } else {
            host
        }
        return "$sanitizedHost:$port"
    }

    companion object {
        private const val KEY_HOST = "config_host"
        private const val KEY_PORT = "config_port"
    }
}
