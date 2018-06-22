load("//src:opts.bzl", "copts", "linkopts")

cc_library(
    name = "value",
    visibility = ["//visibility:public"],
    copts = copts,
    linkopts = linkopts,
    srcs = [
        ":value.cpp",
    ],
    hdrs = [
        ":value.hpp",
    ],
)

cc_test(
    name = "value-test",
    copts = copts + [
        "-Iexternal/com_google_googletest/include",
    ],
    linkopts = linkopts,
    srcs = [
        ":value_test.cpp",
    ],
    deps = [
        "@com_google_googletest//:main",
        "//src/heap",
        "//src/value",
    ],
)
