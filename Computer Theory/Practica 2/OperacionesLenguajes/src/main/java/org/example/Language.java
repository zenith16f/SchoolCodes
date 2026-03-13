package org.example;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

/**
 * Representa un lenguaje formal. Diseñado de forma inmutable.
 */
public class Language {

    private final Set<String> strings;

    public Language(Set<String> strings) {
        // Se usa un Set no modificable para garantizar la inmutabilidad de la clase
        this.strings = Collections.unmodifiableSet(new HashSet<>(strings));
    }

    public Language union(Language other) {
        // Complejidad Temporal: O(|L1| + |L2|) promedio
        Set<String> result = new HashSet<>(this.strings.size() + other.strings.size());
        result.addAll(this.strings);
        result.addAll(other.strings);
        return new Language(result);
    }

    public Language concatenate(Language other) {
        // Preasignación de memoria espacial para evitar el costo de rehashing: O(|L1| * |L2|)
        int initialCapacity = Math.max(16, this.strings.size() * other.strings.size());
        Set<String> result = new HashSet<>(initialCapacity);

        for (String x : this.strings) {
            for (String y : other.strings) {
                result.add(x + y);
            }
        }
        return new Language(result);
    }

    public Language power(int n) {
        // Validación del requerimiento: Rango de -5 a 8
        if (n < -5 || n > 8) {
            throw new IllegalArgumentException("Error: El rango de las potencias debe ser de -5 a 8.");
        }

        // Reflexión para potencias negativas
        if (n < 0) {
            return this.power(-n).reflect();
        }

        // L⁰ = { ε }
        if (n == 0) {
            return new Language(Set.of(""));
        }

        // OPTIMIZACIÓN 1: Short-circuit (Evaluación perezosa para casos base)
        // Si L = ∅, entonces Lⁿ = ∅ (para n > 0).
        // Si L = { ε }, entonces Lⁿ = { ε }.
        // Retornamos la instancia actual en O(1) de tiempo y espacio.
        if (this.strings.isEmpty() || (this.strings.size() == 1 && this.strings.contains(""))) {
            return this;
        }

        // OPTIMIZACIÓN 2: Evitar concatenación inútil con el elemento neutro { ε }
        Language result = null;
        Language base = this;
        int exp = n;

        while (exp > 0) {
            if (exp % 2 == 1) {
                // Asignamos directamente la primera vez en lugar de iterar sobre { ε }
                result = (result == null) ? base : result.concatenate(base);
            }
            exp /= 2;

            // OPTIMIZACIÓN 3: Prevención de explosión combinatoria
            if (exp > 0) {
                base = base.concatenate(base);
            }
        }

        return result;
    }

    public Language positiveClosure() {
        // La práctica requiere calcular exactamente hasta la 4ta potencia [cite: 18]
        Language result = this; // L¹
        for (int i = 2; i <= 4; i++) {
            result = result.union(this.power(i));
        }
        return result;
    }

    public Language kleeneClosure() {
        // Kleene es la cerradura positiva unida con L⁰ (vacío/epsilon) hasta la 4ta potencia
        return this.power(0).union(this.positiveClosure());
    }

    public Language reflect() {
        Set<String> result = new HashSet<>(this.strings.size());
        for (String w : this.strings) {
            result.add(new StringBuilder(w).reverse().toString());
        }
        return new Language(result);
    }

    public Set<String> getStrings() {
        return strings;
    }

    // Formateo para la salida estándar
    @Override
    public String toString() {
        return "{ " + String.join(", ", strings.stream()
                .map(s -> s.isEmpty() ? "ε" : s) // Mostramos la cadena vacía como epsilon
                .toList()) + " }";
    }
}