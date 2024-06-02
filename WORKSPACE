new_local_repository(
    name = "ray_api",
    path = "/home/zwx/anaconda3/envs/torch_v1_13_0/lib/python3.8/site-packages/ray/cpp",
    build_file_content = """
cc_library(
    name = "ray_api",
    srcs = glob(["lib/*.so"]),
    hdrs = glob(["include/**/*.h", "include/**/*.hpp"]),
    includes = ["include"],
    linkopts = ["-Wl,-rpath"],
    visibility = ["//visibility:public"],
)
    """
)

