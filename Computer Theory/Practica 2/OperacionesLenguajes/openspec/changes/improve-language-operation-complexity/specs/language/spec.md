# Delta for Language

## ADDED Requirements

### Requirement: Optimized Closure Algorithms

The system MUST implement optimized closure algorithms to prevent exponential time complexity in worst-case scenarios.

#### Scenario: Positive Closure with Limited Results

- GIVEN a language L with 10 strings of average length 3
- WHEN positive closure (L⁺) is computed with a maximum string count limit of 100
- THEN the operation MUST complete within 100ms
- AND the result MUST NOT exceed 100 strings
- AND the result MUST include all valid concatenations up to the limit

#### Scenario: Kleene Closure with Safety Limits

- GIVEN a language L with 5 strings of average length 2
- WHEN kleene closure (L*) is computed with maximum string count limit of 50
- THEN the operation MUST complete within 50ms
- AND the result MUST not exceed 50 strings 
- AND the result MUST include empty string plus valid concatenations up to the limit

### Requirement: Memoization for Language Operations

The system SHOULD implement memoization to avoid redundant computations in repeated operations.

#### Scenario: Repeated Power Operation

- GIVEN a language L with 3 strings
- WHEN power operation (L³) is computed twice consecutively
- THEN the first computation MUST be cached
- AND the second computation MUST return cached result
- AND both operations MUST complete within expected time limits

## MODIFIED Requirements

### Requirement: Union Operation Performance

The system SHALL maintain O(n+m) time complexity for union operations where n and m are the sizes of the input languages.

#### Scenario: Union of Large Languages

- GIVEN two languages L1 with 1000 strings and L2 with 500 strings  
- WHEN union (L1 ∪ L2) is performed
- THEN operation MUST complete within 10ms
- AND the result MUST contain all strings from both languages exactly once
- AND the time complexity MUST remain linear with respect to the sum of language sizes

### Requirement: Concatenation Operation Efficiency  

The system SHALL maintain O(n×m) time complexity for concatenation operations.

#### Scenario: Concatenation with Large Languages 

- GIVEN two languages L1 with 200 strings and L2 with 150 strings
- WHEN concatenation (L1 · L2) is performed  
- THEN operation MUST complete within 50ms
- AND the result MUST contain all valid pairwise concatenations
- AND the time complexity MUST remain proportional to the product of language sizes

## REMOVED Requirements

### Requirement: Unbounded Closure Growth

(Reason: This requirement was removed due to performance concerns - closure operations must now respect safety limits to prevent exponential blowup)