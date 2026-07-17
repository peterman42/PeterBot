package com.peterbot.android.ui.theme

import android.app.Activity
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.darkColorScheme
import androidx.compose.material3.lightColorScheme
import androidx.compose.runtime.Composable
import androidx.compose.runtime.SideEffect
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.toArgb
import androidx.compose.ui.platform.LocalView
import androidx.core.view.WindowCompat

// ── Palette ──────────────────────────────────────────────────────────────
private val Cyan400        = Color(0xFF26C6DA)
private val Cyan200        = Color(0xFF80DEEA)
private val Cyan700        = Color(0xFF0097A7)
private val DarkSurface    = Color(0xFF0F1923)
private val DarkBackground = Color(0xFF0A1017)
private val DarkCard       = Color(0xFF162230)
private val ErrorRed       = Color(0xFFEF5350)
private val SuccessGreen   = Color(0xFF66BB6A)

private val DarkColorScheme = darkColorScheme(
    primary            = Cyan400,
    onPrimary          = Color.Black,
    primaryContainer   = Cyan700,
    onPrimaryContainer = Cyan200,
    secondary          = Color(0xFF4DD0E1),
    onSecondary        = Color.Black,
    tertiary           = SuccessGreen,
    background         = DarkBackground,
    onBackground       = Color(0xFFE0E0E0),
    surface            = DarkSurface,
    onSurface          = Color(0xFFE0E0E0),
    surfaceVariant     = DarkCard,
    onSurfaceVariant   = Color(0xFFB0BEC5),
    error              = ErrorRed,
    onError            = Color.Black,
    outline            = Color(0xFF37474F),
    outlineVariant     = Color(0xFF263238),
)

private val LightColorScheme = lightColorScheme(
    primary            = Cyan700,
    onPrimary          = Color.White,
    primaryContainer   = Cyan200,
    onPrimaryContainer = Color(0xFF004D56),
    secondary          = Color(0xFF00838F),
    onSecondary        = Color.White,
    tertiary           = Color(0xFF388E3C),
    background         = Color(0xFFF5F8FA),
    onBackground       = Color(0xFF1B1B1F),
    surface            = Color.White,
    onSurface          = Color(0xFF1B1B1F),
    surfaceVariant     = Color(0xFFE0F2F1),
    onSurfaceVariant   = Color(0xFF49454F),
    error              = Color(0xFFD32F2F),
    onError            = Color.White,
    outline            = Color(0xFFB0BEC5),
    outlineVariant     = Color(0xFFE0E0E0),
)

@Composable
fun PeterBotTheme(
    darkTheme: Boolean = isSystemInDarkTheme(),
    content: @Composable () -> Unit
) {
    val colorScheme = if (darkTheme) DarkColorScheme else LightColorScheme

    val view = LocalView.current
    if (!view.isInEditMode) {
        SideEffect {
            val window = (view.context as Activity).window
            @Suppress("DEPRECATION")
            window.statusBarColor = colorScheme.background.toArgb()
            WindowCompat.getInsetsController(window, view).isAppearanceLightStatusBars = !darkTheme
        }
    }

    MaterialTheme(
        colorScheme = colorScheme,
        content = content
    )
}
