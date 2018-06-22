load("//src:opts.bzl", "copts", "linkopts")

cc_library(
    name = "utility",
    visibility = ["//visibility:public"],
    copts = copts,
    linkopts = linkopts,
    srcs = [
        ":io.cpp",
    ],
    hdrs = [
        ":align.hpp",
        ":io.hpp",
        ":likely.hpp",
    ],
)
