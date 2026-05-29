package com.peterbot.shared.data.network

import io.ktor.client.HttpClient
import io.ktor.client.request.get
import io.ktor.client.statement.HttpResponse
import io.ktor.http.isSuccess

class RobotHttpClient(
    private val client: HttpClient,
    private val hostProvider: () -> String
) {
    suspend fun forward(): Result<Unit> = sendCommand(0)
    suspend fun backward(): Result<Unit> = sendCommand(1)
    suspend fun turnRight(): Result<Unit> = sendCommand(2)
    suspend fun turnLeft(): Result<Unit> = sendCommand(3)
    suspend fun stop(): Result<Unit> = sendCommand(4)

    private suspend fun sendCommand(commandId: Int): Result<Unit> {
        return try {
            val host = hostProvider().removeSuffix("/")
            val url = "$host/move/$commandId"
            val response: HttpResponse = client.get(url)
            if (response.status.isSuccess()) {
                Result.success(Unit)
            } else {
                Result.failure(Exception("Server returned status: ${response.status}"))
            }
        } catch (e: Exception) {
            Result.failure(e)
        }
    }
}
