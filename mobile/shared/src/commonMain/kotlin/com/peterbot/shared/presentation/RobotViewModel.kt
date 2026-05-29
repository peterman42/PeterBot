package com.peterbot.shared.presentation

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.peterbot.shared.data.network.RobotHttpClient
import com.peterbot.shared.domain.repository.ConfigRepository
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch

data class RobotUiState(
    val host: String = "",
    val port: String = "",
    val isConfigSaved: Boolean = false,
    val isLoading: Boolean = false,
    val statusMessage: String? = null,
    val isError: Boolean = false
)

class RobotViewModel(
    private val configRepository: ConfigRepository,
    private val httpClient: RobotHttpClient
) : ViewModel() {

    private val _uiState = MutableStateFlow(RobotUiState())
    val uiState: StateFlow<RobotUiState> = _uiState.asStateFlow()

    init {
        val savedHost = configRepository.getHost() ?: "192.168.4.1"
        val savedPort = configRepository.getPort() ?: 80
        _uiState.update {
            it.copy(
                host = savedHost,
                port = savedPort.toString(),
                isConfigSaved = configRepository.getHost() != null
            )
        }
    }

    fun onHostChanged(newHost: String) {
        _uiState.update { it.copy(host = newHost, statusMessage = null) }
    }

    fun onPortChanged(newPort: String) {
        _uiState.update { it.copy(port = newPort, statusMessage = null) }
    }

    fun saveConfig() {
        val currentHost = _uiState.value.host.trim()
        val currentPort = _uiState.value.port.toIntOrNull()

        if (currentHost.isEmpty()) {
            _uiState.update { it.copy(statusMessage = "Host cannot be empty", isError = true) }
            return
        }
        if (currentPort == null || currentPort !in 1..65535) {
            _uiState.update { it.copy(statusMessage = "Invalid port number", isError = true) }
            return
        }

        configRepository.saveConfig(currentHost, currentPort)
        _uiState.update {
            it.copy(
                isConfigSaved = true,
                statusMessage = "Configuration saved!",
                isError = false
            )
        }
    }

    fun editConfig() {
        _uiState.update { it.copy(isConfigSaved = false) }
    }

    fun moveForward() = executeCommand { httpClient.forward() }
    fun moveBackward() = executeCommand { httpClient.backward() }
    fun turnLeft() = executeCommand { httpClient.turnLeft() }
    fun turnRight() = executeCommand { httpClient.turnRight() }
    fun stop() = executeCommand { httpClient.stop() }

    private fun executeCommand(commandBlock: suspend () -> Result<Unit>) {
        viewModelScope.launch {
            _uiState.update { it.copy(isLoading = true, statusMessage = null) }
            val result = commandBlock()
            if (result.isSuccess) {
                _uiState.update {
                    it.copy(
                        isLoading = false,
                        statusMessage = "Command executed successfully",
                        isError = false
                    )
                }
            } else {
                val errorMsg = result.exceptionOrNull()?.message ?: "Unknown error"
                _uiState.update {
                    it.copy(
                        isLoading = false,
                        statusMessage = "Failed: $errorMsg",
                        isError = true
                    )
                }
            }
        }
    }
}
