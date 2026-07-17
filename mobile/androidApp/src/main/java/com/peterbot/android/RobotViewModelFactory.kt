package com.peterbot.android

import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import com.peterbot.shared.data.network.RobotHttpClient
import com.peterbot.shared.domain.repository.ConfigRepository
import com.peterbot.shared.presentation.RobotViewModel

class RobotViewModelFactory(
    private val configRepository: ConfigRepository,
    private val httpClient: RobotHttpClient
) : ViewModelProvider.Factory {
    @Suppress("UNCHECKED_CAST")
    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(RobotViewModel::class.java)) {
            return RobotViewModel(configRepository, httpClient) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class: ${modelClass.name}")
    }
}
