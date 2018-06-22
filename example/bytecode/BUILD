genrule(
    name = "generate",
    srcs = [
        ":generate.pl",
    ],
    outs = [
        ":system.sksys",
    ],
    cmd = """
        set -o errexit
        perl $(SRCS) > $(OUTS)
    """,
)
