<head>
	<link rel="stylesheet" type="text/css" href="./util/mdstyle.css">
</head>

<h4>NOTE: This README is a work in progress<h4>

<img src="./img/titleScreen.PNG" title="Title Screen" alt="Star Lord Title Screen" align="middle" />

<h2>0) Intro</h2>

+ Star Lord is a third person space shooter based on a game I built while at the University of Mary Washington. It's a heavy object oriented design, coded in C++ while working in the VisualStudio environment. As such, you won't see a Makefile in here - I relied on VisualStudio to do all that under the hood. 

+ Star Lord also relies heavily on the <a href="liballeg.org">Allegro Game Programming Library</a>, which, while robust, has certain limitations compared to other libraries. However, it provides enough 'barebones' functionality to allow Star Lord to be a fully functional - and importantly, entertaining - arcade-like game.

+ The object was to create a game that you might find in an arcade. I've always wanted to purchase an arcade machine for my house; however, the costs are often outrageous, plus there really isn't much you can do with the game after you've played it through. It's static. You can't customize it. Ergo, the Star Lord project was born with the intent of creating the software I could throw into a custom built, stand up arcade machine. 

<h2>1) Getting this code into VisualStudio</h2>

+ Quick run down of what you need to do:

	+ Create a project in Visual Studio. 

	+ Create a dependency on the Allegro library. 

	+ Dump the following directories into the project:

		+ /font
		+ /img
		+ /music
		+ /sound

	+ Dump the following files into the project:

		Name | Source | Header
		--- | ---: | ---:
		asteroid | .cpp | .h
		crate | .cpp  | .h
		enemy | .cpp | .h
		friend | .cpp | .h
		gameState | .cpp | .h
		gameplay | .cpp | .h
		hull | .cpp | .h
		laser | .cpp | .h
		main | .cpp | 
		soldier | .cpp | .h
		special | .cpp | .h
		weapon | .cpp | .h

+ Detailed run down of how to do this:

	+ TODO 

