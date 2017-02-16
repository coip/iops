# simplex
tableaus on tableaus

##Mon, Oct 03, 2016  6:49:45 PM
-	started project.
-	started builder.c:
	-	file streams working, pass the file in as argv[1].
		-	*file must follow format: { int, int, ..., int }*

	-	supports 100char lines.
	-	On that note, currently only working by char.(as opposed to int)
	-	__parsing in c is fun__
	-	###Successfully### pulls char-for-char, any ',' & [0-9] for storing in a dynamically allocated char*.
	-	converting to ints in progress.
Tue, Oct 04, 2016 12:09:44 AM
overhauled memory management to be more efficient before the real processing happens, to mitigate waste via allocation and more processing intensive work on the matrices
Thu Feb 16 14:22:56 STD 2017
finished builder.c for v1
starting github.io page/wiki.
planning to write out roadmap

build out matrix.c for matrix operations next.
