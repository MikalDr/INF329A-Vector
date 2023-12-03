## Haskell List Functions for Numbers Checklist

### Basic Operations
- [ ] `(++)` - List concatenation.
- [ ] `length` - Returns the length of a list.
- [ ] `null` - Checks if a list is empty.
- [ ] `reverse` - Reverses a list.
- [ ] `append`
- [ ] `postpend`
- [ ] `prepend`

### Transformations
- [ ] `map` - Applies a function to every element of a list.
- [ ] `filter` - Filters a list based on a predicate.
- [ ] `take` - Takes the first n elements of a list.
- [ ] `drop` - Drops the first n elements from a list.
- [ ] `takeWhile` - Takes elements from the list as long as the predicate holds.
- [ ] `dropWhile` - Drops elements from the list as long as the predicate holds.
- [ ] `scanl` - Similar to foldl, but returns a list of successive reduced values.
- [ ] `scanr` - Similar to foldr, but returns a list of successive reduced values.
- [ ] `concat`
- [ ] `concatMap`

### Folding and Reduction
- [ ] `foldl` - Left-associative fold of a list.
- [ ] `foldr` - Right-associative fold of a list.
- [ ] `sum` - Calculates the sum of a list.
- [ ] `product` - Calculates the product of a list.

### Searching
- [ ] `elem` - Checks if an element is in a list.
- [ ] `maximum` - Returns the maximum value from a list.
- [ ] `minimum` - Returns the minimum value from a list.

### Sublists and Elements
- [ ] `subsequences` - Returns all subsequences of the list.
- [ ] `permutations` - Returns all permutations of the list.
- [ ] `head` - Extracts the first element of a list.
- [ ] `last` - Extracts the last element of a list.
- [ ] `tail` - Extracts all elements after the head of a list.
- [ ] `init` - Extracts all elements except the last from a list.
- [ ] `splitAt`
- [ ] `span`

### Zipping and Unzipping
- [ ] `zip` - Takes two lists and returns a list of corresponding pairs.
- [ ] `zipWith` - Generalized version of zip, with a function to combine elements.

### Specialized Lists
- [ ] `replicate` - Creates a list where an element is repeated n times.
- [ ] `cycle` - Repeats a list infinitely.
- [ ] `iterate` - Generates an infinite list by repeatedly applying a function.

