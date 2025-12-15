
package com.rishu;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.File;

public class Compiler {

    public static void main(String[] args) throws Exception {
        
        String[] compileCmd = {
                "g++", "-std=c++17", "-pthread",
                "-Icpp-src/Crow/include",
                "-Icpp-src/asio/include",
                "cpp-src/mains.cpp",
                "-o", "cpp-src/mains.exe",
                "-lws2_32",
                "-lmswsock"
        };

        System.out.println("Compiling C++ database engine...\n");

        ProcessBuilder compilePb = new ProcessBuilder(compileCmd);
        compilePb.redirectErrorStream(true);

        Process compileProcess = compilePb.start();

        try (BufferedReader reader =
                     new BufferedReader(new InputStreamReader(compileProcess.getInputStream()))) {

            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }

        int exitCode = compileProcess.waitFor();
        System.out.println("\nCompilation finished with exit code: " + exitCode);

        if (exitCode != 0) {
            System.out.println("Compilation failed. Not running the DB engine.");
            return;
        }


        System.out.println("\nRunning database engine...\n");

        File exe = new File("cpp-src/mains.exe");

        ProcessBuilder runPb = new ProcessBuilder(exe.getAbsolutePath());
        runPb.directory(new File("cpp-src"));   // keep working dir correct
        runPb.inheritIO();
        Process dbProcess = runPb.start();
        dbProcess.waitFor();

    }
}
// /*

// /// RUN THIS COMMAND ALWAYS
// cd C:\Users\imris\Desktop\DevOps\cpp-db-wrapper

// mvn clean
// mvn package

// java -jar target\cpp-db-wrapper-1.0-SNAPSHOT.jar
// */