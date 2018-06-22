load("//src:opts.bzl", "copts", "linkopts")

cc_library(
    name = "debug",
    visibility = ["//visibility:public"],
    copts = copts,
    linkopts = linkopts,
    srcs = [
        ":value.cpp",
    ],
    hdrs = [
        ":value.hpp",
    ],
    deps = [
        "//src/value",
    ],
)
