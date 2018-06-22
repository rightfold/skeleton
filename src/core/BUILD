load("//src:opts.bzl", "copts", "linkopts")

cc_library(
    name = "core",
    visibility = ["//visibility:public"],
    copts = copts,
    linkopts = linkopts,
    srcs = [
        ":interpret.cpp",
        ":thread.cpp",
    ],
    hdrs = [
        ":program.hpp",
        ":interpret.hpp",
        ":thread.hpp",
    ],
    deps = [
        "//src/heap",
        "//src/value",
    ],
)

cc_test(
    name = "core-test",
    copts = copts + [
        "-Iexternal/com_google_googletest/include",
    ],
    linkopts = linkopts,
    srcs = [
        ":interpret_test.cpp",
    ],
    deps = [
        "@com_google_googletest//:main",
        "//src/core",
        "//src/heap",
        "//src/value",
    ],
)
