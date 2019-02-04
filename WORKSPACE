load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest",
    tag = "release-1.8.1",
)

new_local_repository(
    name = "opencv",
    build_file = "BUILD.opencv",
    path = "/home/hannes/opencv_install/opencv-4.0.1",
)
