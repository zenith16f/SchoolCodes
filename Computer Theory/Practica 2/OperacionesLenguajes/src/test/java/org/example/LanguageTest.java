package org.example;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.util.Set;
import java.util.HashSet;

class LanguageTest {
    
    // Helper method to create Language from varargs
    Language lang(String... strings) {
        return new Language(new HashSet<>(Set.of(strings)));
    }
    
    // ==================== UNION TESTS ====================
    
    @Test
    void testUnion_ofTwoNonOverlappingLanguages() {
        Language L1 = lang("a", "ab");
        Language L2 = lang("b", "ba");
        
        Language result = L1.union(L2);
        
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("ab"));
        assertTrue(result.getStrings().contains("b"));
        assertTrue(result.getStrings().contains("ba"));
        assertEquals(4, result.getStrings().size());
    }
    
    @Test
    void testUnion_ofTwoOverlappingLanguages() {
        Language L1 = lang("a", "b");
        Language L2 = lang("b", "c");
        
        Language result = L1.union(L2);
        
        assertEquals(3, result.getStrings().size());
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("b"));
        assertTrue(result.getStrings().contains("c"));
    }
    
    @Test
    void testUnion_withEmptyLanguage() {
        Language L1 = lang("a", "b");
        Language L2 = lang();
        
        Language result = L1.union(L2);
        
        assertEquals(2, result.getStrings().size());
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("b"));
    }
    
    // ==================== CONCATENATION TESTS ====================
    
    @Test
    void testConcatenation_basic() {
        Language L1 = lang("a", "ab");
        Language L2 = lang("b", "ba");
        
        Language result = L1.concatenate(L2);
        
        assertTrue(result.getStrings().contains("ab"));
        assertTrue(result.getStrings().contains("aba"));
        assertTrue(result.getStrings().contains("abb"));
        assertTrue(result.getStrings().contains("abba"));
        assertEquals(4, result.getStrings().size());
    }
    
    @Test
    void testConcatenation_withEmptyString() {
        Language L1 = lang("a", "b");
        Language L2 = lang("");
        
        Language result = L1.concatenate(L2);
        
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("b"));
        assertEquals(2, result.getStrings().size());
    }
    
    @Test
    void testConcatenation_withEmptyLanguage() {
        Language L1 = lang("a", "b");
        Language L2 = lang();
        
        Language result = L1.concatenate(L2);
        
        assertTrue(result.getStrings().isEmpty());
    }
    
    // ==================== POWER TESTS ====================
    
    @Test
    void testPower_zero() {
        Language L = lang("a", "b");
        
        Language result = L.power(0);
        
        assertEquals(1, result.getStrings().size());
        assertTrue(result.getStrings().contains(""));
    }
    
    @Test
    void testPower_one() {
        Language L = lang("a", "b");
        
        Language result = L.power(1);
        
        assertEquals(2, result.getStrings().size());
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("b"));
    }
    
    @Test
    void testPower_two() {
        Language L = lang("a", "b");
        
        Language result = L.power(2);
        
        assertEquals(4, result.getStrings().size());
        assertTrue(result.getStrings().contains("aa"));
        assertTrue(result.getStrings().contains("ab"));
        assertTrue(result.getStrings().contains("ba"));
        assertTrue(result.getStrings().contains("bb"));
    }
    
    @Test
    void testPower_three() {
        Language L = lang("a", "b");
        
        Language result = L.power(3);
        
        assertEquals(8, result.getStrings().size());
    }
    
    // ==================== POSITIVE CLOSURE TESTS ====================
    
    @Test
    void testPositiveClosure() {
        Language L = lang("a", "b");
        
        Language result = L.positiveClosure();
        
        // Should contain all strings of length >= 1
        assertFalse(result.getStrings().contains(""));  // L⁺ does NOT include ε
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("b"));
        assertTrue(result.getStrings().contains("aa"));
        assertTrue(result.getStrings().contains("ab"));
        assertTrue(result.getStrings().contains("ba"));
        assertTrue(result.getStrings().contains("bb"));
    }
    
    @Test
    void testPositiveClosure_withEmptyString() {
        Language L = lang("");
        
        Language result = L.positiveClosure();
        
        // When L = {ε}, L⁺ = {ε}
        assertEquals(1, result.getStrings().size());
        assertTrue(result.getStrings().contains(""));
    }
    
    // ==================== KLEENE CLOSURE TESTS ====================
    
    @Test
    void testKleeneClosure() {
        Language L = lang("a", "b");
        
        Language result = L.kleeneClosure();
        
        // L* ALWAYS includes ε
        assertTrue(result.getStrings().contains(""));
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("b"));
        assertTrue(result.getStrings().contains("aa"));
    }
    
    @Test
    void testKleeneClosure_alwaysHasEpsilon() {
        Language L = lang("a", "b");
        
        Language result = L.kleeneClosure();
        
        assertTrue(result.getStrings().contains(""));
    }
    
    // ==================== REFLECTION TESTS ====================
    
    @Test
    void testReflect_basic() {
        Language L = lang("abc", "a", "bb");
        
        Language result = L.reflect();
        
        assertTrue(result.getStrings().contains("cba"));
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("bb"));
        assertEquals(3, result.getStrings().size());
    }
    
    @Test
    void testReflect_ofEmptyString() {
        Language L = lang("a", "");
        
        Language result = L.reflect();
        
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains(""));
        assertEquals(2, result.getStrings().size());
    }
    
    @Test
    void testReflect_ofPalindrome() {
        Language L = lang("aba", "aa");
        
        Language result = L.reflect();
        
        assertTrue(result.getStrings().contains("aba"));  // palindrome unchanged
        assertTrue(result.getStrings().contains("aa"));  // palindrome unchanged
    }
    
    // ==================== DIFFERENCE TESTS ====================
    
    @Test
    void testDifference_ofTwoNonOverlappingLanguages() {
        Language L1 = lang("a", "ab");
        Language L2 = lang("b", "ba");
        
        Language result = L1.difference(L2);
        
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("ab"));
        assertEquals(2, result.getStrings().size());
    }
    
    @Test
    void testDifference_ofTwoOverlappingLanguages() {
        Language L1 = lang("a", "b", "c");
        Language L2 = lang("b", "c", "d");
        
        Language result = L1.difference(L2);
        
        assertTrue(result.getStrings().contains("a"));
        assertFalse(result.getStrings().contains("b"));
        assertFalse(result.getStrings().contains("c"));
        assertEquals(1, result.getStrings().size());
    }
    
    @Test
    void testDifference_withEmptyLanguage() {
        Language L1 = lang("a", "b");
        Language L2 = lang();
        
        Language result = L1.difference(L2);
        
        assertTrue(result.getStrings().contains("a"));
        assertTrue(result.getStrings().contains("b"));
        assertEquals(2, result.getStrings().size());
    }
    
    @Test
    void testDifference_withIdenticalLanguages() {
        Language L1 = lang("a", "b");
        Language L2 = lang("a", "b");
        
        Language result = L1.difference(L2);
        
        assertTrue(result.getStrings().isEmpty());
    }
    
    // ==================== IMMUTABILITY TESTS ====================
    
    @Test
    void testImmutability_union() {
        Language L1 = lang("a");
        Language L2 = lang("b");
        
        Language result = L1.union(L2);
        
        // Original should be unchanged
        assertTrue(L1.getStrings().contains("a"));
        assertFalse(L1.getStrings().contains("b"));
        assertEquals(1, L1.getStrings().size());
    }
    
    @Test
    void testImmutability_concatenate() {
        Language L1 = lang("a");
        Language L2 = lang("b");
        
        Language result = L1.concatenate(L2);
        
        // Original should be unchanged
        assertTrue(L1.getStrings().contains("a"));
        assertFalse(L1.getStrings().contains("ab"));
    }
    
    @Test
    void testImmutability_power() {
        Language L = lang("a");
        
        Language result = L.power(2);
        
        // Original should be unchanged
        assertTrue(L.getStrings().contains("a"));
        assertFalse(L.getStrings().contains("aa"));
    }
}
