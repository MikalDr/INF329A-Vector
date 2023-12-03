## Haskell List Functions for Numbers Checklist

### Basic Operations
- [x] `(++)/get` - List concatenation.
- [x] `length` - Returns the length of a list.
- [x] `null` - Checks if a list is empty.
- [x] `reverse` - Reverses a list.
- [x] `append`
- [x] `postpend`
- [x] `prepend`

### Transformations
- [x] `map` - Applies a function to every element of a list.
- [x] `filter` - Filters a list based on a predicate.
- [x] `take` - Takes the first n elements of a list.
- [x] `drop` - Drops the first n elements from a list.
- [x] `takeWhile` - Takes elements from the list as long as the predicate holds.
- [x] `dropWhile` - Drops elements from the list as long as the predicate holds.
- [x] `scanl` - Similar to foldl, but returns a list of successive reduced values.
- [x] `scanr` - Similar to foldr, but returns a list of successive reduced values.
- [x] `scanl1`
- [x] `scanr1`
- [x] `concat`
- [x] `concatMap`

### Folding and Reduction
- [x] `foldl` - Left-associative fold of a list.
- [x] `foldr` - Right-associative fold of a list.
- [x] `sum` - Calculates the sum of a list.
- [x] `product` - Calculates the product of a list.
- [x] `and`
- [x] `or`

### Searching
- [x] `elem` - Checks if an element is in a list.
- [x] `notElem`
- [x] `lookup`
- [x] `maximum` - Returns the maximum value from a list.
- [x] `minimum` - Returns the minimum value from a list.

### Sublists and Elements
- [x] `head` - Extracts the first element of a list.
- [x] `last` - Extracts the last element of a list.
- [x] `tail` - Extracts all elements after the head of a list.
- [x] `init` - Extracts all elements except the last from a list.
- [x] `splitAt`
- [x] `span`
- [x] `break`

### Zipping and Unzipping
The zipping functions are not for numerals
- [x] `zip` - Takes two lists and returns a list of corresponding pairs.
- [x] `zipWith` - Generalized version of zip, with a function to combine elements.
- [x] `unzip`
- [ ] `zip3`
- [ ] `zipWith3`
- [ ] `unzip3`

### Specialized Lists
- [x] `replicate` - Creates a list where an element is repeated n times.
- [ ] `cycle` - Repeats a list infinitely.
- [ ] `iterate` - Generates an infinite list by repeatedly applying a function.

