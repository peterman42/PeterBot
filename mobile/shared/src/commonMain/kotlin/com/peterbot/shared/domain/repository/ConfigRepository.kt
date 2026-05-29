package com.peterbot.shared.domain.repository

interface ConfigRepository {
    fun getHost(): String?
    fun getPort(): Int?
    fun saveConfig(host: String, port: Int)
    fun getBaseUrl(): String
}
