package com.peterbot.shared

interface Platform {
    val name: String
}

expect fun getPlatform(): Platform
