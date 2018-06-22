load("//src:opts.bzl", "copts", "linkopts")

cc_library(
    name = "heap",
    visibility = ["//visibility:public"],
    copts = copts,
    linkopts = linkopts,
    srcs = [
        ":arena.cpp",
        ":heap.cpp",
        ":leak.cpp",
    ],
    hdrs = [
        ":arena.hpp",
        ":heap.hpp",
        ":leak.hpp",
    ],
    deps = [
        "//src/utility",
        "//src/value",
    ],
)
