package(default_visibility = ["//visibility:public"])

load(":conf.bzl", "GOSSIP_MAINNET_VARIABLES")
load(":conf.bzl", "GOSSIP_TESTNET_VARIABLES")

config_setting(
    name = "mainnet",
    values = {"define": "network=mainnet"},
)

config_setting(
    name = "testnet",
    values = {"define": "network=testnet"},
)

cc_library(
    name = "conf",
    srcs = ["conf.c"],
    hdrs = ["conf.h"],
    defines = select({
        ":mainnet": GOSSIP_MAINNET_VARIABLES,
        ":testnet": GOSSIP_TESTNET_VARIABLES,
        "//conditions:default": GOSSIP_MAINNET_VARIABLES,
    }),
    visibility = ["//visibility:public"],
    deps = [
        "//common:errors",
        "//common/trinary:trit_byte",
    ],
)

cc_library(
    name = "iota_packet",
    srcs = ["iota_packet.c"],
    hdrs = ["iota_packet.h"],
    deps = [
        ":conf",
        "//common:errors",
        "//common/model:transaction",
        "//common/network:endpoint",
        "//common/trinary:bytes",
        "//common/trinary:flex_trit",
        "@com_github_uthash//:uthash",
    ],
)

cc_library(
    name = "neighbor_shared",
    hdrs = ["neighbor.h"],
    deps = [
        ":iota_packet",
        "//common:errors",
    ],
)

cc_library(
    name = "neighbor",
    srcs = ["neighbor.c"],
    deps = [
        ":neighbor_shared",
        ":node_shared",
        "//common/model:transaction",
        "//common/network:uri_parser",
        "//common/trinary:trit_array",
        "//gossip/components:transaction_requester",
        "//gossip/services:tcp_sender",
        "//gossip/services:udp_sender",
    ],
)

cc_library(
    name = "transaction_request",
    hdrs = ["transaction_request.h"],
)

cc_library(
    name = "node_shared",
    hdrs = ["node.h"],
    deps = [
        "//gossip/components:broadcaster_shared",
        "//gossip/components:processor_shared",
        "//gossip/components:receiver_shared",
        "//gossip/components:responder_shared",
        "//gossip/components:transaction_requester",
    ],
)

cc_library(
    name = "node",
    srcs = ["node.c"],
    deps = [
        ":node_shared",
        "//gossip/components:broadcaster",
        "//gossip/components:processor",
        "//gossip/components:receiver",
        "//gossip/components:responder",
    ],
)
