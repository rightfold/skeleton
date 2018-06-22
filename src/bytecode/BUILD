load("//src:opts.bzl", "copts", "linkopts")

cc_library(
    name = "bytecode",
    visibility = ["//visibility:public"],
    copts = copts,
    linkopts = linkopts,
    srcs = [
        ":decode.cpp",
    ],
    hdrs = [
        ":decode.hpp",
    ],
    deps = [
        "//src/core",
        "//src/utility",
    ],
)
