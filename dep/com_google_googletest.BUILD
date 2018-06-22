cc_library(
    name = "main",
    visibility = ["//visibility:public"],
    copts = [
        "-Iexternal/com_google_googletest/include",
    ],
    linkopts = [
        "-pthread",
    ],
    srcs = glob(
        ["src/*.cc"],
        exclude = ["src/gtest-all.cc"],
    ),
    hdrs = glob([
        "include/**/*.h",
        "src/*.h",
    ]),
)
