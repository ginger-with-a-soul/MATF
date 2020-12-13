/*
terms: osnovna struktura podataka (atoms, numbers, variables, compound terms)
atoms: strings - lower, upper, digits, underscore (starts with a lowercase letter)
	'This is also an atom'
numbers: integer type
variables: same as atoms except they start with uppercase or _
	_ - this is an anonymous variable
compound term:
	functor - a prolog atom
	arguments - prolog terms


clauses, programs, queries:
clauses - facts and rules -> they define predicates
	facts - predicate followed by .

rules:
	a predicate :- seq of predicates sep by , ends with a .
			   (if)

programs: a seq of clauses 


built-in predicates: can't be functors and rule heads
	Equality: = (X = Y)
	Guaranteed success and failure: true, fail
	Output: write('string'), nl (newline)
	Checking: atom(elephant)

	Matching - two terms match if they are the same or can become the same when
		they take values
		p(X, 2, 2) = p(1, 2, X) (no because X is already 1)
		p(X, 2, 2) = p(1, 2, _) (yes because _ is unique)
*/