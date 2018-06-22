load("//src:opts.bzl", "copts", "linkopts")

cc_binary(
    name = "main",
    visibility = ["//visibility:public"],
    copts = copts,
    linkopts = linkopts,
    srcs = [
        ":main.cpp",
    ],
    deps = [
        "//src/bytecode",
        "//src/core",
        "//src/debug",
        "//src/heap",
        "//src/utility",
        "//src/value",
    ],
)
