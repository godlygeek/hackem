# HackEM

## Design Goals

**The first goal** of this project is to become the major successor of Slash'EM and port over most of Slash'EM to a modern platform. I chose EvilHack as a base because it is based on 3.6, it's inheritly more difficult, and it contains many Quality Of Life features already baked in. See here:

	- Nice HP Bar
	- Enhance menu shows max and % progress on skills.
	- Extended commands: #terrain, #annotate, #overview, #tip, #give, #adjust splitting and merging
	- Peaceful displacing, paranoid swim, Smart shop autopickup
	- Full bag altar BUC identification
	- New conducts: Elbereth, alignment, touched art, petless
	- New soko levels, new room shapes and themed rooms.
	- object materials, quick wand wresting
	
Evil also has some challenging aspects that are well worth keeping:

	- New roles: Infidel, convict
	- New Races: giant, tortle, centaur, and illithid
	- Elbereth: Can't use unless you found/discovered it.
	- Partial intrinsics; Partial eflection
	- No randomly generated magic markers
	- Strong monsters push through weaker monsters to get to you.
	- Zombies ressurect, mummies wither, spellcasters are meaner.
	- Monster steeds

The rest of the design goals are listed below.

## Installation

Each OS type found under the `sys` folder has an installation guide for that
particular operating system. Pre-compiled binaries (linux and windows) can be
found here - https://github.com/elunna/HackEM/releases

For Linux (TL;DR version):
- Dependencies needed: `make` `gcc` `gdb` `flex` `bison` `libncurses-dev`
- From the desired directory, `git clone https://github.com/elunna/HackEM`
- Navigate to the `HackEM/sys/unix` folder, then `./setup.sh hints/linux` or
  `./setup.sh hints/linux-debug` depending on what you intend to do

  - Using the standard `linux` hints file assumes running as a normal user, and
  game folders and files will reside in `/home/$USER` based on the account used.
  Invoking `sudo` should not be necessary

  - Using the `linux-debug` hints file assumes installing as root, and includes
  extra CFLAGS for debugging in a development scenario

  - With either hints file, edit the install paths to your liking
- Navigate back to the root HackEM folder, and `make all && make install`
- Execute the `HackEM` binary
- In the home directory of the account used to install HackEM, create your
  rc config file - `touch .hackemrc` and then edit as necessary

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

# Todo

## Goal 1: Porting Slash'EM

### Slash'EM monsters:
- [x] giant tick (AT_MULTIPLY)
- [x] giant flea (AT_MULTIPLY)
- [x] snow ant
- [x] giant louse
- [x] tsetse fly
- [x] migo drone (M3_TRAITOR)
- [x] yellow jacket
- [x] black wasp
- [x] migo warrior
- [x] giant wasp
- [x] spitting beetle
- [x] migo queen
- [x] assassin bug (M3_TRAITOR)
- [x] killer beetle
- [x] jiggling blob
- [x] lava blob
- [x] static blob
- [x] burbling blob
- [x] chicken
- [x] cockatoo
- [x] parrot
- [x] pit bull
- [x] dingo puppy
- [x] large dingo
- [x] death dog
- [x] rabid wolf
- [x] wolverine
- [x] shadow wolf (Removed MR_PLUSONE | MR_HITASTWO)
- [x] mist wolf   (Removed MR_PLUSONE | MR_HITASTWO)
- [x] glowing eye
- [x] bloodshot eye
- [x] blinking eye
- [x] werepanther (animal) 	5
- [x] weretiger 	(animal) 	7
- [x] werespider 	(animal) 	11
- [x] weresnake 	(animal) 	9
- [x] werepanther (human) 	5
- [x] werespider 	(human) 	7
- [x] weretiger 	(human) 	9
- [x] weresnake 	(human) 	9
- [x] kamadan
- [x] displacer beast (already present in evil)
- [x] caterwaul
- [x] sabre-toothed cat
- [x] hellcat
- [x] statue gargoyle (Removed MR_PLUSONE and added to nonliving)
- [ ] galltrit (deferred)
- [ ] jermlaine (deferred)
- [x] dwarf thief
- [x] duergar (removed MR_HITASONE)
- [x] deep one (growup done)
- [x] deeper one (growup done)
- [x] deepest one
- [x] dretch
- [x] rutterkin
- [x] nupperibo
- [x] blood imp
- [x] clear jelly
- [x] yellow jelly
- [x] orange jelly (Implemented passive sleep attacks)
- [x] rancid jelly
- [x] swamp kobold
- [x] rock kobold
- [x] kobold warrior
- [x] Kroo the Kobold King
- [x] leprechaun wizard (Removed MR_HITASONE)
- [x] pixie (removed MR_HITASONE)
- [x] brownie (removed MR_HITASONE)
- [x] quickling (removed MR_HITASONE)
- [ ] Aphrodite - Already in evil, higher level
- [x] war orc
- [x] great orc
- [x] Grund the Orc King
- [x] snow orc
- [x] demon orc
- [x] lamb (Note: grows up)
- [x] sheep (MS_SHEEP)
- [x] goat
- [x] cow (MS_COW)
- [x] bull
- [x] giant badger (changed to rodent class to match honey badger)
- [x] scramper
- [x] squealer
- [x] mangler
- [x] Jumbo the Elephant
- [x] juggernaut
- [x] catoblepas (Removed MR_HITASTWO)
- [x] rabbit
- [x] black rat
- [x] rabid rabbit
- [x] pack rat
- [x] hellrat
- [x] Rat King
- [x] recluse spider (webmaker)
- [x] barking spider (webmaker)
- [x] carrion crawler
- [x] nickelpede
- [x] giant scorpion
- [x] phase spider (webmaker)
- [x] Girtab
- [x] Shelob
- [ ] Pegasus (evil already has pegasi)
- [x] larva (Note: grows up)
- [x] maggot (Note: grows up)
- [x] dung worm
- [x] acid worm
- [x] bloodworm
- [x] tunnel worm
- [x] rot worm
- [x] spark bug (Removed MR_HITASONE)
- [x] arc bug (Removed MR_HITASONE)
- [x] lightning bug (Removed MR_HITASONE)
- [x] echidna
- [x] platypus
- [x] koala
- [x] wombat
- [x] Tasmanian devil
- [x] wallaby
- [x] wallaroo
- [x] kangaroo
- [x] movanic deva (Removed MR_PLUSONE)
- [x] monadic deva (Removed MR_PLUSONE)
- [x] astral deva (Removed MR_PLUSONE)
- [x] Planetar (Removed MR_PLUSFOUR)
- [x] Solar (Removed MR_PLUSFOUR)
- [x] rhumbat
- [x] athol
- [x] hellbat
- [x] mongbat
- [x] mobat
- [x] harpy
- [x] byakhee
- [x] nightgaunt
- [x] baby shimmering dragon (already in EvilHack)
- [x] shimmering dragon 	 (already in EvilHack)

	Note: -- adding dragons is tricky, need to maintain strict orders in code.
- [ ] baby deep dragon
- [ ] deep dragon

- [x] wyvern (Removed MR_HITASTWO)
- [x] hydra  (Removed MR_HITASTWO)
- [x] disgusting mold
- [x] black mold
- [x] gnome thief
- [x] deep gnome (Removed MR_HITASONE)
- [x] gnome warrior (Removed MR_HITASONE)
- [x] Ruggo the Gnome King (Removed MR_HITASONE)

- [ ] gnoll (evil already has) (Note: grows up)
- [ ] gnoll warrior (Note: grows up)
- [ ] gnoll chieftain
- [ ] gnoll shaman
	- [ ] Evil also has gnoll cleric and gnoll hunter, check if these are clones or new monsters.
	
- [x] The Largest Giant (Removed MR_HITASTHREE)
- [x] Father Dagon (deferred)
- [x] Mother Hydra (deferred)
- [ ] vorpal jabberwock (already has the beheading attack!)
- [x] troll mummy (Added regen and stalk, revival works fine.)
- [x] ogre mage
- [x] shadow ogre (Removed MR_PLUSONE)
- [x] moldy pudding (Removed MR_HITASONE, added M4_VULNERABLE_FIRE)
- [x] shoggoth (Note: grows up)
- [x] giant shoggoth
- [x] genetic engineer (already in evil)
- [x] Doctor Frankenstein
- [x] king cobra
- [x] asphynx
- [x] two-headed troll (Removed MR_HITASTWO)
- [x] black troll (Removed MR_HITASTHREE)
- [x] water hulk (Removed MR_HITASONE)
- [x] fire vampire
- [x] star vampire
- [ ] vampire mage (already in evil)
- [x] wight
- [x] zruty
- [x] ghoul mage
- [x] ghast
- [x] ghoul queen
- [x] gug
- [x] wax golem
- [x] plastic golem
- [x] Frankenstein's Monster
- [x] ruby golem
- [x] diamond golem
- [x] sapphire golem
- [x] steel golem (Added M4_VULNERABLE_ACID)
- [x] crystal golem
- [x] gibberling
- [x] grimlock
- [x] drow (Added infravisible)
- [x] mugger
- [x] gypsy (Added M3_INFRAVISIBLE)
- [x] black marketeer (Removed MR_HITASFOUR, added M3_ACCURATE)
- [x] shadow (Added M3_INFRAVISION)
- [x] spined devil (Removed MR_PLUSONE)
- [x] bearded devil (Removed MR_PLUSONE | MR_HITASTWO)
- [x] bar-lgura (Removed MR_PLUSONE | MR_HITASTWO)
- [x] chasme (Removed MR_PLUSONE | MR_HITASTWO)
- [x] babau (MR_PLUSONE | MR_HITASTWO)
- [x] nabassu (Removed MR_PLUSONE | MR_HITASTHREE)
- [ ] Cthulhu (deferred)
- [x] giant crab
- [x] gila monster
- [x] rhaumbusun
- [ ] basilisk (already in evil)
- [x] komodo dragon
- [x] bad egg
- [x] killer tripe ration
- [x] killer food ration
- [x] pile of killer coins (Note: grows up)
- [x] large pile of killer coins (Note: grows up)
- [x] huge pile of killer coins
- [ ] Nightmare (evil has nightmares)
- [ ] Beholder (evil has beholders)
- [ ] Vecna (evil has Vecna already)
- [x] flame mage
- [x] ice mage
- [x] necromancer
- [x] undead slayer
- [x] yeoman
- [x] High Flame Mage (Removed MR_HITASFOUR)
- [x] High Ice Mage (Removed MR_HITASFOUR)
- [x] Dark Lord (Reoved MR_HITASFOUR)
- [x] Van Helsing (Removed MR_HITASFOUR)
- [x] Chief Yeoman Warder
- [x] Water Mage (Removed MR_HITASFOUR)
- [x] Earth Mage (Removed MR_HITASFOUR)
- [x] Maugneshaagar (Removed MR_HITASFOUR)
- [x] Count Dracula (removed MR_HITASFOUR)
- [x] Colonel Blood
- [x] igniter (Removed MR_HITASONE)
- [x] froster (Removed MR_HITASONE)
- [x] embalmer (Removed MR_HITASONE)
- [x] exterminator (Removed MR_HITASONE)
- [x] Yeoman Warder
	
	
Quality control on monsters:
	- [ ] Double-check and redo all difficulty levels for imported monsters.
	- [ ] Double check all monsters for secondary references in code (other effects/abilities, etc)
	- [ ] Also look at what monsters are normally equipped with.
	- [ ] Update database knowledge entries for every new monster
	- [ ] Update monsters.map of the tiles
	- [ ] Import all tiles for new monsters	
	- [ ] Update infravision tags. Only body heat should be visible.
	- [ ] For everything that had MARM - maybe use the y value instead? Look into how monsters are armed, this must be related.
	- [ ] Add alternate spellings


Other ideas:
	- [ ] Add message for tick/flea multiplication?
	- [ ] Allow ticks and fleas to appear in main dungeon? (They currently only appear in the lawful quest or Gehennom.
	- [ ] Make mist wolves leave trail of mist? (Like hezrous leave gas clouds)
	- [ ] Werespiders should summon more types: giant spiders, jumping spiders, recluse and cave spiders.
	- [ ] Set up the sabre-tooth cat to grow up into the tiger?
	- [ ] Make sabre-tooth cat a little weaker, or tiger stronger.
	- [ ] Put statue gargoyle in immune_death_magic, remove from nonliving list.
	- [ ] Check town/minetown for dwarf thief/gnome thief placement
	- [ ] Make blood imps, nupperibos drain levels as well?
	- [ ] Blood imps should probably have a vampiric attack.
	- [ ] clear jelly has touch acid attack, but not passive. Add passive acid?
	- [ ] yellow jelly has passive stun, but not active. add passive acid?
	- [ ] orange jelly has passive sleep, but not active attack. add passive acid?
 	- [ ] rancid jelly should leave a trail of acid slime?
	- [ ] Should rancid jelly eat organics?
	- [ ] blue/spotted/ochre jellies seem vulnerable to fire, but new jellies are not in slashem. Should they be? Or vulnerable to something else?
	- [ ] Make were-critters summon more diversity of monsters
	- [ ] Check other monsters for traitor property
	- [ ] What can we replace requiresX and hitsAsX with? Forceful hits, more AC/MR
	- [ ] Update mines.des to include different types of gnomes, dwarves, and thieves.
	- [ ] Kobolds use the orc sounds, maybe they should have their own sounds?
	- [ ] Add traitor property to all kobolds
	- [ ] Upgrade giant badger to be much stronger, and maybe grow up into honey badger?
	- [ ] Badgers can usually swim; add M1_SWIM?
	- [ ] Usually known as stinky animals due to their ability of release a nasty odor from their well-developed anal scent glands. Add a poison gas cloud trail?
	- [ ] Most badgers are solitary, nocturnal animals. (spawn in very small groups, they like the dark)
	- [ ] Honey badgers should love bee hives... and be mortal enemies with bees (or team a)
	- [ ] catoblepas: The gaze attack doesn't seem to give a message when you die. The reason for death is "gaze of death"
	- [ ] Make centipede grow into nickelpede
	- [ ] Make nickelpede grow into giant centipede
	- [ ] make phase spiders more powerful and skittish? Make them have phasing?
	- [ ] Dung worms should be poisonous?
	- [ ] Eating dung worms should cause illness?
	- [ ] allow "blood worm", "blood-worm" as spelling
	- [ ] Hellbat "pecks". Should be bite. 
	- [ ] Check that other bats don't peck - they don't have beaks...
	- [ ] Let Shadow Ogres appear in the main dungeon (or at least genennom)
	- [ ] Moldy pudding: Enhance a bit, only has an engulfing organic attack. No damage.
	- [ ] Remove all but one corrosion attack from shoggoths and giant shoggoths.
	- [ ] Water hulks: Add vulnerability to shock (similar to other water-critters)
	- [ ] Why do we have wights?  Should they not be more powerful than barrow wights?
	- [ ] Implement gypsy_chat
	- [ ] Should komodo dragon/gila monster be vulnerable to cold?
	- [ ] Make evil food vulnerable to fire - "cooking"!
	- [ ] Make leprechauns and evil gold mortal enemies
	- [ ] Compare basilisk to slashem, keep the 'c' symbol?
	
### Slash'EM Items
Artifacts:
- [ ] Bat from Hell
- [ ] Deathsword
- [ ] Deep Freeze
- [ ] Deluder
- [ ] Disrupter
- [ ] Doomblade
- [ ] Elfrist
- [ ] Firewall
- [ ] Gauntlets of Defense
- [ ] Giantkiller
- [ ] Hellfire
- [ ] Holy Spear of Light
- [ ] Houchou
- [ ] Luckblade
- [ ] Mirrorbright
- [ ] Plague
- [ ] Quick Blade
- [ ] Reaper
- [ ] Serpent's Tongue
- [ ] Skullcrusher
- [ ] Sword of Balance
- [ ] Sword of Justice
- [ ] Thiefbane
- [ ] Wallet of Perseus
- [ ] Werebane
- [ ] Whisperfeet
- [ ] The Candle of Eternal Flame
- [ ] The Storm Whistle
- [ ] Great Dagger of Glaurgnaa
- [ ] Stake of Van Helsing
- [ ] Crown of Saint Edward
- [ ] Nighthorn
- [ ] Eye of the Beholder
- [ ] Hand of Vecna
- [ ] Key of Law
- [ ] Key of Neutrality
- [ ] Key of Chaos


Slashem Items:
- [ ] Dark elven dagger
- [ ] Wooden stake
- [ ] Great dagger
- [ ] Silver short sword
- [ ] Dark elven short sword
- [ ] Silver long sword
- [ ] Rapier
- [ ] Fly swatter
- [ ] Silver mace
- [ ] Heavy hammer
- [ ] Dark elven bow
- [ ] Dark elven arrow
- [ ] Pistol				(maybe keep?)
- [ ] Submachine gun 		(probably cut)
- [ ] Heavy machine gun 	(probably cut)
- [ ] Rifle 				(probably cut)
- [ ] Assault rifle 		(probably cut)
- [ ] Sniper rifle 		(probably cut)
- [ ] Shotgun 			(probably cut)
- [ ] Auto shotgun 		(probably cut)
- [ ] Rocket launcher 	(probably cut)
- [ ] Grenade launcher 	(probably cut)
- [ ] Bullet 				(maybe keep?)
- [ ] Silver bullet		(maybe keep?)
- [ ] Shotgun shell		(probably cut)
- [ ] Rocket 				(probably cut)
- [ ] Frag grenade		(keep but altar?)
- [ ] Gas grenade			(keep but altar?)
- [ ] Stick of dynamite	(archaeologist specialty?)

- [ ] Mood ring
- [ ] Ring of sleeping
- [ ] Ring of gain dexterity
- [ ] Ring of gain intelligence
- [ ] Ring of gain wisdom

- [ ] Amulet of flying
- [ ] Amulet of drain resistance
- [ ] Amulet versus stone

- [ ] Magic candle
- [ ] Torch
- [ ] Medical kit			(cut this?)
- [ ] Fishing pole
- [ ] Green lightsaber	(probably cut)
- [ ] Blue lightsaber		(probably cut)
- [ ] Red lightsaber		(probably cut)
- [ ] Red double lightsaber (probably cut)

- [ ] Asian pear
- [ ] Mushroom
- [ ] Sandwich
- [ ] Tortilla
- [ ] Cheese
- [ ] Pill
- [ ] Holy wafer

- [ ] Potion of amnesia
- [ ] Potion of blood
- [ ] Potion of vampire blood
- [ ] Potion of clairvoyance
- [ ] Potion of ESP
- [ ] Potion of invulnerability

- [ ] Spellbook of flame sphere
- [ ] Spellbook of freeze sphere
- [ ] Spellbook of resist poison
- [ ] Spellbook of resist sleep
- [ ] Spellbook of endure cold
- [ ] Spellbook of endure heat
- [ ] Spellbook of insulate
- [ ] Spellbook of poison blast
- [ ] Spellbook of lightning
- [ ] Spellbook of acid stream
- [ ] Spellbook of enlighten
- [ ] Spellbook of command undead
- [ ] Spellbook of summon undead
- [ ] Spellbook of passwall
- [ ] Spellbook of enchant weapon (probably cut)
- [ ] Spellbook of enchant armor  (probably cut)

- [ ] Wand of healing
- [ ] Wand of extra healing
- [ ] Wand of draining
- [ ] Wand of fear
- [ ] Wand of create horde
- [ ] Wand of fireball

- [ ] Healthstone
- [ ] Whetstone

Slashem Armor:
- [ ] Dark elven mithril-coat
- [ ] Robe of protection
- [ ] Robe of power
- [ ] Robe of weakness
- [ ] Shimmering dragon scales
- [ ] Deep dragon scales
- [ ] Shimmering dragon scale mail
- [ ] Deep dragon scale mail
- [ ] Lab coat
- [ ] Poisonous cloak
- [ ] Gauntlets of swimming

### Roles:
- [ ] Flame Mage
- [ ] Ice Mage
- [ ] Yeoman
- [ ] Undead Slayer
- [ ] Necromancer

- [ ] Monk: Implement the monk closer to Slashem

### Races:
- [ ] Doppleganger
- [ ] Hobbit
- [ ] Vampire
- [ ] Lycanthrope		(probably cut this race, it severely sucks as is)
- [ ] Drow

### Special Levels:
- [ ] Mall
- [ ] Rat level
- [ ] Kobold level
- [ ] Mine king level
- [ ] Grund's Stronghold
- [ ] Lawful Quest
- [ ] Neutral Quest
- [ ] Chaotic Quest
- [ ] Storage room
- [ ] Wyrm Caves
- [ ] The Lost Tomb
- [ ] One-eyed Sam's Black Market
- [ ] Nymph level
- [ ] The Spider Caves
- [ ] The Guild of Disgruntled Adventurers
- [ ] The Sunless Sea
- [ ] The Temple of Moloch
- [ ] The Giant Caverns
- [ ] New Demon Prince Lairs
- [ ] Yeenoghu's lair
- [ ] Demogorgon's lair
- [ ] Geryon's lair
- [ ] Dispater's lair
- [ ] Frankenstein's Lab


### New special rooms
- [ ] Giant Throne Rooms
- [ ] Fungus Farm
- [ ] Real Zoo
- [ ] Bad Food Shop
- [ ] Dragons Lair
- [ ] Lemure Pit 		(only appears in Gehennom)
- [ ] Migo Hive

### Slashem Mechanics:
- [ ] Toilets
- [ ] Mold/Fungus ressurection
- [ ] Temp polymorph
- [ ] Upgrading
- [ ] Invisible items
- [ ] Poison missiles
- [ ] Techniques
- [ ] Shopkeeper services
- [ ] Minion Summoning (Prayer/Altar Gifts)
- [ ] Require-X-to-hit monsters
- [ ] Hits-as-a-+X-weapon
- [ ] Spell minions/entities
- [ ] Gauntlets of power change
- [ ] Unicorn Horn mechanic change
- [ ] No Mysterious Force
- [ ] \#youpoly command
- [ ] \#technique command
- [ ] \#borrow command
	

## Goal 2: Integrate slashem updates and bugfixes from other Slash'EM forks

	- Notably from slashem-up, slashem9, and SlashTHEM.
	- Slash'EM was a great game, but it was far from perfect. It would be nice to polish up things that were left behind (examples: updates to artifacts and quest artifacts, technique bugs, mold mechanics, polymorph bugs (ie: flame mage and ice mage).
	- https://github.com/BarclayII/slashem-up
	- https://github.com/Soviet5lo/SlashTHEM
	- https://github.com/moon-chilled/slashem9
	
	
## Goal 3: Remove/edit Evil content

	- differentiate this fork from EvilHack.
	- Let's use what makes sense - but when in doubt: 
		"Depart from evil, and do good; Seek peace, and pursue it." - Psalm 34:13-14

Examples of what to change back to traditional slashem behavior:
	- Don't require defeating Goblin king to access mines
	- Change sokobon prize system back to normal
	- Return shopkeeper pricing to normal levels (for easier price-ID)
	- Allow entering quest at 10 without penalty
	
	[ ] Don't require defeating Goblin king to access mines
	[] Remove Goblin King level (or repurpose somewhere else)
	[ ] Remove Kathryn Ice Queen branch (or remix)
	
	[ ] Change sokobon prize back to normal
	[ ] Return shopkeeper pricing back to normal (no racist pricing!)
	[ ] Fix paranoid swim
	[ ] Remove water from Gnomish Mines (use in a different mines - wyrm or kobold caves?
	[ ] Remove most random water in early game (ex: No water around up/down stairs)
	[ ] No alignment penalty in quest
	[ ] Can enter quest at 10 - no penalty

	[ ] Revenants should shoot missiles/fireballs (ala Doom)
	[ ] Snowball attack for ice trolls? frost giants?
	[ ] Double check that all nobles are lords, royals are kings.
	[ ] Revert "noble" to "lord"
	[ ] Revert "royal" to "king"
	[ ] Eventually add in the opposite genders from 3.7 (ladies/queens, etc)

	[ ] Keep evil Gnolls or use slashem ones, or ones from Splice/Dnh/Gnollhack?
	[ ] Keep Vecna's lair? 

	[ ] Unrestrict two-weaponing, and let player's get full benefits from both weapons, regardless of primary hand.
	[ ] Possibly go back to traditional altar sacrifice system
	
	[ ] No autopickup when falling through holes?
	
## Goal 4: Import content from other forks.

Bring in new and interesting content from the many quality forks out there.  I'd like to try not to get too wacky and keep to the spirit of Slashem. (And yes, I realize that slashem does get a bit wacky with things like Tasmanian Devils, toilets, and lightsabers - but there are limits!)

	- [ ] Bag of tricks patch (from UnNethack)
	- [ ] Auto-ID of obvious things (UnNethack)
	- [ ] Cartomancer role, Mermaid race (Splicehack)
	- [ ] Boots of Stomping (Splice)
	- [ ] Sheol branch (Un)
	- [ ] 0 turn weapon switching (dnh)
	- [ ] slotless awesome artifacts (dnh)
	- [ ] Cross skill training: From dyna?
	- [ ] Shield/armor skills: Dyna? (Should not just depend on time - but on usage, similar to weapons)

	
## Goal 5: Homemade Ideas/Improvements for Slashem

	- enhance the existing content from slash'em to make more sense, be more challenging, and use the mechanics in more creative ways. 
	- When it makes sense, we'll follow the conventions that Evil has set down, otherwise we might have to invent new mechanics or abilities.

	- [ ] Pokedex for Monsters
	- [ ] Pokedex for Items
	- [ ] Techniques from SlashEm/Them
	- [ ] Add back best roles from SlashThem
		Convict (already in Evil)
		Chef, 
		Drunk, 
		Gladiator, 
		Pirate/Corsair (or copy from Splice) 
		Warrior (revamp to be more in line with Gauntlet)
	- [ ] Add back these races from SlashThem
		[ ] Ghoul
		[e] Giant
		[e] Illithid
		[ ] Vampire
	- [ ] Allow Giants to benefit from ring of slow digestion
	- [ ] Change Gypsy to Fortune Teller and create a "fortune teller wish flag" that once set disallows additional fortune teller wishes.
	- [ ] Fix Sokoban so that monsters don't spawn in the hallway and also probably no peaceful spawns in sokoban.  Both are extremely boring when they happen.  One of the variants has this, so you should be able to patch from them.
		
	- [ ] Instead of fungus: larva/Maggots grows in some corpses, large ones?
	- [ ] Maggots could grow into other things depending on level?
	- [ ] Should water monsters have water attack? Spit water?
	- [ ] shadow monsters leave trail of darkness
	- [ ] Shadow monsters are drain/death/cold resistant?
	- [ ] Anything that is "rockish", ie, rock kobolds, rock gnomes, should be stoning resistant and vulnerable to digging. Stone giant.
	
	
	- [ ] Regarding temp polymorph - there are pros and cons to keeping and removing it. 
		Temp poly items nerfs polymorph a bit, not so much for potions and scrolls, but moreso for rings and amulets (and wands)
		Temp poly introduces another descriptor "hazy" in the inventory.
		Temp poly opens doors up for strange bugs - like +99 dwarven pick-axes.
		
		Temp poly for monsters is much more powerful - werecritters are annoyingly powerful
		Chameleons/shapechangers can unfairly revert multiple consecutive turns after being killed over and over.
		Pet chameleons are formidable pets, they can get killed over and over, and still come back.
		
		I'm more in favor of NOT re-implementing temp poly and keeping the traditional behavior in vanilla and evil.
	
	- [ ] Shopkeeper services
		- the interface needs a revamp, it's really annoying to navigate the shk services in slashem.
		- Implement a nice menu when you press 'p' 
		- (then we can use services even if we own money)
		- General stores should not always allow full identify services for everything. There should be more variety in what they can id - or each one has somem different specialties
		- Slashem stores typically did not have many interesting services. What can we add to make things more interesting?
	
	- [ ] Remove A for All Items (help prevent interface screw, cancelling BoH)
	
	- [ ] More breakable items? 
	- [ ] Blindfolds/towels can burn up? Towels get better because you can moist them
		Can we wet towels in evil?
	
	- [ ] Nerf excalibur - or at least, make it so only lawful knights can get Excalibur.
	- [ ] Make Mjollnir Great, but it demands worthiness. 
		- [ ] Mjollnir is normally extremely heavy but gets lighter with positive alignment.
		- [ ] Make it intelligent
		- [ ] It Has Force Attacks, shock is reduced so people are not dissuaded by it's item destruction. 
		- [ ] Maybe it should just not destroy items anymore...
		- [ ] Has some similarities to MagicBane - it randomly Blinds, stuns, confuses
		- [ ] grants Warning against cross-aligned?


	- [ ] "Force/Impact attacks" are like magical shoves or piledrivers. They make enemies drop items, 
	
	

## Goal 6: HackEM specific content

Create some new content that is specific to HackEM!  

	- [ ] Energy Vampires/Psychic Vampires: 
		Inspired by: https://whatwedointheshadows.fandom.com/wiki/Psychic_vampires
		Drain energy merely by talking to them
		bore - sleep
		daywalkers, not affected by sun
		Can drain other EVs
	
	- [ ] Giant enhancements:
		* Make giants have more elementals associated with their attacks:
			Fire giants have fire attack/fireballs, passive fire. Fire trail/smoke trail
			Frost giants have cold attack/ice balls, passive cold. Ice trail.
			Storm giants = shock
		* Giants can grab/crush/toss you
		* Giants have bellow/holler attack (like Splice sonic attack)
		* Giants can jump and create pits.
		* Thrown boulders hurt a LOT more.

	- [ ] Lord/Prince classes could be able to summon small crowds of lower minions? Or even higher?
	- [ ] Is there special handling for multi-headed monsters? Hydras, 2-headed trolled?
		Afffects things, beheading, regeneration, sight, etc...
	- [ ] Nagas are a little boring, is there anything we can do to spice them up? They are basically mirroring dragons but weaker.
	- [ ] Make see invisible temporary (from potions, eating stalkers, fountains)
		Requires ring to be permanent.

	
	- [ ] Enemy compounds could even have cannons?...
	
	- [ ] Add some passive spells for ice/flame mage?  Ice globe, ring of fire. 
	- [ ] Explosive Barrels (from Doom)
	
	Firearms updates:
	- [ ] Instead of modern firearms - add old-style guns?
	- [ ] Revolver - from Alone in the Dark
	- [ ] Muskets: https://en.wikipedia.org/wiki/Musket
	- [ ] Low gun skill means a gun has a chance of jamming
	- [ ] Higher gun skill is better accuracy, higher damage, and less chance of jamming.

	In Alone in the Dark you can retrieve the revolver in a side room of Derceto's kitchen . Examining the pile of coal that will be on the ground you will be able to recover a shoe box inside which the gun is hidden. The revolver will initially contain 6 bullets, to which 12 more can be added in the Cellar of the villa and on the dresser of one of the guest bedrooms on the first floor. Despite the difficulty pointing and the slowness of fire is a good weapon to defend against slower enemies, causing serious damage. Unlike the gun cartridges, the revolver ammunition will not become useless when the player enters the water making the weapon effective in all situations.



	
	
## Goal 8: Rethinking dungeon texture
	Every 5-9 levels, change the theme of the section. 
		* Populate with mostly related monsters, related special rooms.
		
	Don't change the first 9ish levels: But don't allow new special room types until level 8.
	Level 8: We start to see poly traps, but also weirdly shaped rooms.
	
	
	Gardens/plains: sparse trees, fountains, grass, high grass
	Swamps: water, shallow water, swamp, 
	Wastelands/Desert: burnt trees, boulders, 
	
	Courtyard gardens: Pre-castle levels 
	Castle:
	Under castle:
		* Castle storage, kitchen, stores
		* Utility rooms, Sewers
		* Castle Catacombs/dungeons, torture chambers

		* Secret passages/tunnels - to secret chambers.
		* These eventually lead outside to VoTD.
		
	9-17: special rooms, coordinated rooms
	18-27: wilderness? trees, gardens, zoos, 
	
	
## Goal 7: Rethinking Gehennom
	[ ] polluted fountains: For orctown, and deeper levels, swamp levels?
	[ ] Some room and corridor layouts in gehennom - but with a twist?? (This would potentially allow lemure pits)
	[ ] Interspersed in between levels are room and corridor levels that look ripped from SLEX
		(Crazy colors, textures, maybe even take the R&C generator from slex just for this purpose.)
	[ ] No regen in gehennom
	[ ] Limited power regen in nom.
	[ ] Varia suit damage in certain gehennom levels/rooms (very hot/toxic rooms)
	
## Bugs and fixes
