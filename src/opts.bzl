copts = [
    "-std=c++1z",

    "-Wall",
    "-Wextra",
    "-Wpedantic",

    "-fsanitize=address",
    "-fsanitize=undefined",
]

linkopts = [
    "-fsanitize=address",
    "-fsanitize=undefined",
]
