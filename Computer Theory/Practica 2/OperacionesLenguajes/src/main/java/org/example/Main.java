package org.example;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Set;
import java.util.stream.Collectors;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);
    private static Language l1, l2, l3;

    public static void main(String[] args) {
        System.out.println("=== Práctica 2: Operaciones entre Lenguajes ===");

        // Cargar los 3 archivos iniciales [cite: 5, 10]
        l1 = loadLanguageFromFile("l1.txt");
        l2 = loadLanguageFromFile("l2.txt");
        l3 = loadLanguageFromFile("l3.txt");

        boolean flag = true;
        // El programa no termina hasta que el usuario lo indique
        while (flag) {
            System.out.println("\n--- MENÚ PRINCIPAL ---");
            System.out.println("1. Unión (Seleccionar 2 lenguajes) [cite: 15, 21]");
            System.out.println("2. Concatenación (Seleccionar 2 lenguajes) [cite: 16, 21]");
            System.out.println("3. Potencia (Seleccionar 1 lenguaje) [cite: 17, 22]");
            System.out.println("4. Cerradura Positiva (Seleccionar 1 lenguaje) [cite: 18, 22]");
            System.out.println("5. Cerradura de Kleene (Seleccionar 1 lenguaje) [cite: 19, 22]");
            System.out.println("6. Reflexión (Seleccionar 1 lenguaje) [cite: 19, 22]");
            System.out.println("7. Salir");
            System.out.print("Elige una opción: ");

            String option = scanner.nextLine();
            try {
                processOption(option);
            } catch (Exception e) {
                System.out.println("Error procesando la operación: " + e.getMessage());
            }
        }
    }

    private static void processOption(String option) {
        if (option.equals("7")) {
            System.out.println("Saliendo del programa...");
            System.exit(0); // Termina la ejecución
        }

        Language result = null;

        switch (option) {
            case "1":
                result = selectLanguage("primero").union(selectLanguage("segundo"));
                break;
            case "2":
                result = selectLanguage("primero").concatenate(selectLanguage("segundo"));
                break;
            case "3":
                Language langToPower = selectLanguage("operar");
                System.out.print("Introduce la potencia (-5 a 8): ");
                int power = Integer.parseInt(scanner.nextLine());
                result = langToPower.power(power);
                break;
            case "4":
                result = selectLanguage("operar").positiveClosure();
                break;
            case "5":
                result = selectLanguage("operar").kleeneClosure();
                break;
            case "6":
                // Reflexión equivale a potencia -1
                result = selectLanguage("operar").power(-1);
                break;
            default:
                System.out.println("Opción no válida.");
                return;
        }

        // Mostrar el lenguaje resultante
        System.out.println("\n-> Lenguaje Resultante:");
        System.out.println(result);

        // Función opcional: Guardar archivo
        System.out.print("\n¿Deseas guardar el resultado en un archivo? (s/n): ");
        if (scanner.nextLine().trim().equalsIgnoreCase("s")) {
            saveLanguageToFile(result);
        }
    }

    private static Language selectLanguage(String order) {
        System.out.print("Selecciona el " + order + " lenguaje (1, 2 o 3): ");
        String choice = scanner.nextLine();
        return switch (choice) {
            case "2" -> l2;
            case "3" -> l3;
            default -> l1;
        };
    }

    private static Language loadLanguageFromFile(String name) {
        while (true) {
            System.out.print("Introduce la ruta para el " + name + "[cite: 10]: ");
            String pathStr = scanner.nextLine();
            try {
                Path path = Paths.get(pathStr);
                String content = Files.readString(path);
                // Extraer palabras separadas por espacios
                Set<String> words = Arrays.stream(content.split("\\s+"))
                        .filter(s -> !s.isEmpty())
                        .collect(Collectors.toSet());
                System.out.println("Cargado con " + words.size() + " palabras.");
                return new Language(words);
            } catch (IOException e) {
                System.out.println("Error al leer el archivo. Intenta nuevamente.");
            }
        }
    }

    private static void saveLanguageToFile(Language language) {
        System.out.print("Introduce el nombre o ruta del archivo de salida: ");
        String pathStr = scanner.nextLine();
        try {
            String content = String.join(" ", language.getStrings());
            Files.writeString(Paths.get(pathStr), content);
            System.out.println("Archivo guardado exitosamente.");
        } catch (IOException e) {
            System.out.println("Error al guardar el archivo: " + e.getMessage());
        }
    }
}