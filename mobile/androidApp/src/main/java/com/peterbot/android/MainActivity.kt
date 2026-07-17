package com.peterbot.android

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.animation.Crossfade
import androidx.compose.animation.core.tween
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.systemBarsPadding
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.lifecycle.viewmodel.compose.viewModel
import com.peterbot.android.ui.screens.ConfigScreen
import com.peterbot.android.ui.screens.ControlScreen
import com.peterbot.android.ui.theme.PeterBotTheme
import com.peterbot.shared.data.local.AndroidKeyValueStorage
import com.peterbot.shared.data.network.RobotHttpClient
import com.peterbot.shared.data.repository.ConfigRepositoryImpl
import com.peterbot.shared.presentation.RobotViewModel
import io.ktor.client.HttpClient
import io.ktor.client.engine.okhttp.OkHttp

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        enableEdgeToEdge()
        super.onCreate(savedInstanceState)

        // ── Manual DI ───────────────────────────────────────────
        val storage = AndroidKeyValueStorage(applicationContext)
        val configRepository = ConfigRepositoryImpl(storage)
        val ktorClient = HttpClient(OkHttp)
        val robotHttpClient = RobotHttpClient(ktorClient) { configRepository.getBaseUrl() }
        val factory = RobotViewModelFactory(configRepository, robotHttpClient)

        setContent {
            PeterBotTheme {
                val viewModel: RobotViewModel = viewModel(factory = factory)
                val uiState by viewModel.uiState.collectAsState()

                Crossfade(
                    targetState = uiState.isConfigSaved,
                    animationSpec = tween(400),
                    label = "screenTransition",
                    modifier = Modifier
                        .fillMaxSize()
                        .systemBarsPadding()
                ) { configSaved ->
                    if (configSaved) {
                        ControlScreen(
                            uiState = uiState,
                            onForward = viewModel::moveForward,
                            onBackward = viewModel::moveBackward,
                            onLeft = viewModel::turnLeft,
                            onRight = viewModel::turnRight,
                            onStop = viewModel::stop,
                            onEditConfig = viewModel::editConfig
                        )
                    } else {
                        ConfigScreen(
                            uiState = uiState,
                            onHostChanged = viewModel::onHostChanged,
                            onPortChanged = viewModel::onPortChanged,
                            onSaveConfig = viewModel::saveConfig
                        )
                    }
                }
            }
        }
    }
}
