package com.peterbot.android.ui.screens

import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import com.google.android.exoplayer2.ExoPlayer
import com.google.android.exoplayer2.MediaItem
import com.google.android.exoplayer2.ui.StyledPlayerView

@Composable
fun VideoStreamScreen(
    videoUrl: String,
    modifier: Modifier = Modifier
) {
    Box(
        modifier = modifier
            .fillMaxSize(),
        contentAlignment = Alignment.Center
    ) {
        StyledPlayerView(
            context = LocalContext.current,
            player = ExoPlayer.Builder(LocalContext.current).build().apply {
                setMediaItem(MediaItem.fromUri(videoUrl))
                prepare()
                play()
            },
            modifier = Modifier.fillMaxSize()
        )
    }
}

@Preview(showBackground = true)
@Composable
fun VideoStreamScreenPreview() {
    VideoStreamScreen(videoUrl = "https://example.com/stream")
}
