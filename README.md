# Introduction

This project is a WIP! BlinkNet is a fixed + human ported cross platform low-level reliable UDP socket library from a largely vibecoded project I did this year! BlinkNet aims to be:

- A typed message API networking API that attempts to (respectfully) mimic the flavour of contemporary high level socket libraries like NodeJS (On<T> / Send<T>) with reliable-ordered and unreliable channels, and fragmentation for messages up to 16 KB
- The library should have selective-repeat reliability with per-packet ACKs, RFC 6298 adaptive retransmission timeout and a congestion window

With that said, thank you for being patient, I'll see you in a months time!