const std = @import("std");

pub fn build(b: *std.Build) void {
    const exe = b.addExecutable(.{
        .name = "zcal",
        .target = b.standardTargetOptions(.{}),
        .optimize = b.standardOptimizeOption(.{}),
    });

    exe.addIncludePath(b.path("src"));

    exe.addCSourceFiles(.{
        .files = &.{
            "src/main.c",
        },
        .flags = &.{
            // Compile code according to the ISO C17 standard
            // "-std=c17",
            // Enable most compiler warnings to identify common issues
            "-Wall",
            // Enable additional warnings not covered by -Wall
            "-Wextra",
        },
    });

    exe.linkLibC();

    b.installArtifact(exe);

    const run_exe = b.addRunArtifact(exe);
    const run_step = b.step("run", "Run the application");

    run_step.dependOn(&run_exe.step);
}
