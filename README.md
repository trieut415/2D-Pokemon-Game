A simple 2D Pokemon game, where trainers and pokemon are placed onto a 2D plane currently with a set 
amount of pokemon gyms and centers, where pokemon fight each other and can go to centers to recover.

Here is a description of the commands and their input values:

● m ID x y

● "move": command Trainer ID to move to location (x, y)

● c ID1 ID2

● "move towards a PokemonCenter”: command Trainer ID1 to start heading to
PokemonCenter ID2.

● g ID1 ID2

● “move towards a PokemonGym”: command Trainer ID1 to start heading towards
PokemonGym ID2.

● s ID

● "stop": command Trainer ID to stop doing whatever it is doing

● p ID potion_amount

● “buy potions”: command Trainer ID to buy potion_amount of potion at a
PokemonCenter.

● b ID battle_amount

● “complete battle_amount battles at a PokemonGym”: command Trainer ID to
complete battle_amount of battles at a PokemonGym.

● a

● "advance": advance one-time step by updating each object once.

● r

● "run": advance one-time step and update each object, and repeat until either the
update function returns true for at least one of the objects, or 5 time steps have
been done.

● q

● "quit": terminate the program
