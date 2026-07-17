package com.peterbot.android.ui.screens

import androidx.compose.animation.AnimatedVisibility
import androidx.compose.animation.core.FastOutSlowInEasing
import androidx.compose.animation.core.RepeatMode
import androidx.compose.animation.core.animateFloat
import androidx.compose.animation.core.infiniteRepeatable
import androidx.compose.animation.core.rememberInfiniteTransition
import androidx.compose.animation.core.tween
import androidx.compose.animation.fadeIn
import androidx.compose.animation.fadeOut
import androidx.compose.animation.slideInVertically
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.interaction.MutableInteractionSource
import androidx.compose.foundation.interaction.collectIsPressedAsState
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.FilledIconButton
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButtonDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.drawBehind
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.peterbot.android.R
import com.peterbot.shared.presentation.RobotUiState

@Composable
fun ControlScreen(
    uiState: RobotUiState,
    onForward: () -> Unit,
    onBackward: () -> Unit,
    onLeft: () -> Unit,
    onRight: () -> Unit,
    onStop: () -> Unit,
    onEditConfig: () -> Unit,
    modifier: Modifier = Modifier
) {
    Box(
        modifier = modifier
            .fillMaxSize()
            .background(
                brush = Brush.verticalGradient(
                    colors = listOf(
                        MaterialTheme.colorScheme.background,
                        MaterialTheme.colorScheme.surface,
                    )
                )
            )
    ) {
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(24.dp),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            // ── Header ──────────────────────────────────────────────
            HeaderSection(
                host = uiState.host,
                port = uiState.port,
                onEditConfig = onEditConfig
            )

            Spacer(modifier = Modifier.weight(1f))

            // ── D-Pad ───────────────────────────────────────────────
            DirectionalPad(
                onForward = onForward,
                onBackward = onBackward,
                onLeft = onLeft,
                onRight = onRight,
                onStop = onStop,
                isLoading = uiState.isLoading
            )

            Spacer(modifier = Modifier.weight(1f))

            // ── Status ──────────────────────────────────────────────
            StatusBar(uiState = uiState)
        }
    }
}

@Composable
private fun HeaderSection(
    host: String,
    port: String,
    onEditConfig: () -> Unit
) {
    Row(
        modifier = Modifier.fillMaxWidth(),
        horizontalArrangement = Arrangement.SpaceBetween,
        verticalAlignment = Alignment.CenterVertically
    ) {
        Column {
            Text(
                text = "PeterBot",
                style = MaterialTheme.typography.headlineSmall.copy(
                    fontWeight = FontWeight.Bold,
                    letterSpacing = 1.sp
                ),
                color = MaterialTheme.colorScheme.primary
            )
            Row(verticalAlignment = Alignment.CenterVertically) {
                // Pulsing connection dot
                val infiniteTransition = rememberInfiniteTransition(label = "pulse")
                val pulseAlpha by infiniteTransition.animateFloat(
                    initialValue = 0.4f,
                    targetValue = 1f,
                    animationSpec = infiniteRepeatable(
                        animation = tween(1000, easing = FastOutSlowInEasing),
                        repeatMode = RepeatMode.Reverse
                    ),
                    label = "pulseAlpha"
                )
                Box(
                    modifier = Modifier
                        .size(8.dp)
                        .background(
                            color = MaterialTheme.colorScheme.tertiary.copy(alpha = pulseAlpha),
                            shape = CircleShape
                        )
                )
                Spacer(modifier = Modifier.width(8.dp))
                Text(
                    text = "$host:$port",
                    style = MaterialTheme.typography.bodySmall,
                    color = MaterialTheme.colorScheme.onSurfaceVariant
                )
            }
        }
        TextButton(onClick = onEditConfig) {
            Text(
                "Settings",
                color = MaterialTheme.colorScheme.primary,
                fontWeight = FontWeight.Medium
            )
        }
    }
}

@Composable
private fun DirectionalPad(
    onForward: () -> Unit,
    onBackward: () -> Unit,
    onLeft: () -> Unit,
    onRight: () -> Unit,
    onStop: () -> Unit,
    isLoading: Boolean
) {
    val padColor = MaterialTheme.colorScheme.surfaceVariant.copy(alpha = 0.5f)
    val primaryColor = MaterialTheme.colorScheme.primary

    Box(
        modifier = Modifier
            .size(280.dp)
            .drawBehind {
                // Subtle radial glow behind the pad
                drawCircle(
                    brush = Brush.radialGradient(
                        colors = listOf(
                            primaryColor.copy(alpha = 0.08f),
                            Color.Transparent
                        ),
                        center = Offset(size.width / 2, size.height / 2),
                        radius = size.width * 0.7f
                    )
                )
            },
        contentAlignment = Alignment.Center
    ) {
        // Forward
        DirectionButton(
            iconRes = R.drawable.ic_arrow_up,
            contentDescription = "Forward",
            onClick = onForward,
            modifier = Modifier.align(Alignment.TopCenter)
        )

        // Left
        DirectionButton(
            iconRes = R.drawable.ic_arrow_left,
            contentDescription = "Left",
            onClick = onLeft,
            modifier = Modifier.align(Alignment.CenterStart)
        )

        // Stop (centre)
        StopButton(
            onClick = onStop,
            isLoading = isLoading
        )

        // Right
        DirectionButton(
            iconRes = R.drawable.ic_arrow_right,
            contentDescription = "Right",
            onClick = onRight,
            modifier = Modifier.align(Alignment.CenterEnd)
        )

        // Backward
        DirectionButton(
            iconRes = R.drawable.ic_arrow_down,
            contentDescription = "Backward",
            onClick = onBackward,
            modifier = Modifier.align(Alignment.BottomCenter)
        )
    }
}

@Composable
private fun DirectionButton(
    iconRes: Int,
    contentDescription: String,
    onClick: () -> Unit,
    modifier: Modifier = Modifier
) {
    val interactionSource = remember { MutableInteractionSource() }
    val isPressed by interactionSource.collectIsPressedAsState()

    FilledIconButton(
        onClick = onClick,
        modifier = modifier
            .size(72.dp)
            .shadow(
                elevation = if (isPressed) 8.dp else 4.dp,
                shape = RoundedCornerShape(18.dp),
                ambientColor = MaterialTheme.colorScheme.primary.copy(alpha = 0.3f),
                spotColor = MaterialTheme.colorScheme.primary.copy(alpha = 0.3f)
            ),
        shape = RoundedCornerShape(18.dp),
        colors = IconButtonDefaults.filledIconButtonColors(
            containerColor = MaterialTheme.colorScheme.surfaceVariant,
            contentColor = MaterialTheme.colorScheme.primary
        ),
        interactionSource = interactionSource
    ) {
        Icon(
            painter = painterResource(id = iconRes),
            contentDescription = contentDescription,
            modifier = Modifier.size(28.dp)
        )
    }
}

@Composable
private fun StopButton(
    onClick: () -> Unit,
    isLoading: Boolean
) {
    val interactionSource = remember { MutableInteractionSource() }
    val isPressed by interactionSource.collectIsPressedAsState()

    FilledIconButton(
        onClick = onClick,
        modifier = Modifier
            .size(76.dp)
            .then(
                if (!isLoading) {
                    Modifier.border(
                        width = 2.dp,
                        brush = Brush.linearGradient(
                            colors = listOf(
                                MaterialTheme.colorScheme.error.copy(alpha = 0.6f),
                                MaterialTheme.colorScheme.error.copy(alpha = 0.2f)
                            )
                        ),
                        shape = CircleShape
                    )
                } else Modifier
            ),
        shape = CircleShape,
        colors = IconButtonDefaults.filledIconButtonColors(
            containerColor = MaterialTheme.colorScheme.error.copy(alpha = 0.15f),
            contentColor = MaterialTheme.colorScheme.error
        ),
        interactionSource = interactionSource
    ) {
        Icon(
            painter = painterResource(id = R.drawable.ic_stop),
            contentDescription = "Stop",
            modifier = Modifier.size(32.dp)
        )
    }
}

@Composable
private fun StatusBar(uiState: RobotUiState) {
    AnimatedVisibility(
        visible = uiState.statusMessage != null,
        enter = fadeIn() + slideInVertically { it },
        exit = fadeOut()
    ) {
        uiState.statusMessage?.let { msg ->
            Card(
                modifier = Modifier.fillMaxWidth(),
                shape = RoundedCornerShape(14.dp),
                colors = CardDefaults.cardColors(
                    containerColor = if (uiState.isError) {
                        MaterialTheme.colorScheme.error.copy(alpha = 0.12f)
                    } else {
                        MaterialTheme.colorScheme.tertiary.copy(alpha = 0.12f)
                    }
                ),
                elevation = CardDefaults.cardElevation(defaultElevation = 0.dp)
            ) {
                Text(
                    text = msg,
                    modifier = Modifier.padding(horizontal = 16.dp, vertical = 12.dp),
                    color = if (uiState.isError) {
                        MaterialTheme.colorScheme.error
                    } else {
                        MaterialTheme.colorScheme.tertiary
                    },
                    style = MaterialTheme.typography.bodyMedium.copy(
                        fontWeight = FontWeight.Medium
                    )
                )
            }
        }
    }
}
