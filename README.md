# simpleresolver
Simple DNS address resolver using getaddrinfo

Just calls `getaddrinfo` for an address given on the command line, then `inet_ntop` to convert the information
into a printable IP address. I only wrote it to debug the networking on ultra small docker containers.
