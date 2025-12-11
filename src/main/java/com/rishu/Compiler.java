package com.rishu;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Compiler {
    public static void main(String[] args) throws Exception {

        // Command to compile your C++ DB engine
        String[] cmd = {
                "g++", "-std=c++17", "-pthread",
                "-Icpp-src/Crow/include",
                "-Icpp-src/asio/include",
                "cpp-src/mains.cpp",
                "-o", "cpp-src/mains.exe",
                "-lws2_32",
                "-lmswsock"
        };

        System.out.println("Compiling C++ database engine...\n");

        ProcessBuilder pb = new ProcessBuilder(cmd);
        pb.redirectErrorStream(true);  // merge stderr into stdout

        Process process = pb.start();

        try (BufferedReader reader =
                     new BufferedReader(new InputStreamReader(process.getInputStream()))) {

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }

        int exitCode = process.waitFor();
        System.out.println("\nCompilation finished with exit code: " + exitCode);

        if (exitCode == 0) {
            System.out.println("\nRunning database engine...\n");
            new ProcessBuilder("cpp-src/mains.exe")
                    .inheritIO()
                    .start();
        } else {
            System.out.println("Compilation failed. Not running the DB engine.");
        }
    }
}


/*

/// RUN THIS COMMAND ALWAYS
cd C:\Users\imris\Desktop\DevOps\cpp-db-wrapper

mvn compile
mvn exec:java
*/