#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <list>

using namespace std;

#define INFI 100000

class Node{
private:
	int index;
	unordered_set<int> prevs;
	int dist;
public:
	Node(int _index, int _prev, int _dist) :index(_index), dist(_dist)
	{
		prevs.insert(_prev);
	}

	Node(int _index, unordered_set<int> _prevs, int _dist) :index(_index), prevs(_prevs), dist(_dist){}

	bool Update(int newP, int newD)
	{
		if (newD > dist){
			return false;
		}
		else if (newD == dist)
		{
			prevs.insert(newP);
			return true;
		}
		else
		{
			dist = newD;
			prevs.clear();
			prevs.insert(newP);
			return true;
		}
	}

	unordered_set<int> Prevs()
	{
		return prevs;
	}

	int Index()
	{
		return index;
	}

	int Dist()
	{
		return dist;
	}
};

class Solution {
private:
	int isNeighbor(int a, int b, vector<string> &vec)
	{
		int diffCount = 0;
		string strA = vec[a], strB = vec[b];
		decltype(strA.size()) i = 0;
		
		for (i = 0; i < strA.size(); ++i)
		{
			if (strA[i] != strB[i])
			{
				diffCount++;
			}
		}

		if (diffCount > 1)
		{
			return INFI;	//Not Neighbor
		}
		else
		{
			return diffCount;	//0 - Self, 1 - Neighbor
		}
	}

	template <typename T>
	vector<T> Dict2Vector(unordered_set<T> &dict)
	{
		vector<T> vec;
		for (auto t : dict)
		{
			vec.push_back(t);
		}
		return vec;
	}

	int getIndex(string str, vector<string> vec)
	{
		auto N = vec.size();
		int index = -1;
		for (decltype(N) i = 0; i < N; ++i)
		{
			if (vec[i] == str)
			{
				index = i;
			}
		}
		return index;
	}

	vector<vector<int>> Vec2Dists(vector<string> &vec)
	{
		auto N = vec.size();
		vector<vector<int>> dists;
		for (decltype(N) i = 0; i < N; ++i)
		{
			vector<int> subDists;
			for (decltype(N) j = 0; j < N; ++j)
			{
				subDists.push_back(isNeighbor(i, j, vec));
			}
			dists.push_back(subDists);
		}
		return dists;
	}

	int addDist(int a, int b)
	{
		if (a >= INFI || b >= INFI)
		{
			return INFI;
		}
		else
		{
			return a + b;
		}
	}

	void sortByDist(list<Node> &q)
	{
		q.sort([](Node a, Node b){
			return (a.Dist() < b.Dist());
		}
		);
	}

	void sortByIndex(vector<Node> &q)
	{
		sort(q.begin(), q.end(),
			[](Node a, Node b){
			return (a.Index() < b.Index());
		}
		);
	}

	list<Node> initWaiting(int start, int end, vector<vector<int>> &dists)
	{
		list<Node> Waiting;
		auto N = dists.size();
		for (decltype(N) i = 0; i < N; ++i)
		{
			if (dists[start][i] >= INFI)
			{
				Node n = Node(i, -1, INFI);
				Waiting.push_back(n);
			}
			else
			{
				Node n = Node(i, start, dists[start][i]);
				Waiting.push_back(n);
			}
		}
		sortByDist(Waiting);
		return Waiting;
	}

	vector<vector<int>> getShortestPaths(int start, int end, vector<Node> &Visited)
	{
		vector<vector<int>> paths, restPaths;
		vector<int> path = { end };
		if (Visited[end].Dist() >= INFI)
		{
			return paths;
		}
		else if (start == end)
		{
			paths.push_back(path);
			return paths;
		}
		int last = end;
		while (Visited[last].Prevs().size() == 1)
		{
			last = *(Visited[last].Prevs().begin());
			path.push_back(last);
			if (last == start)
			{
				paths.push_back(path);
				return paths;
			}
		}
		for (auto n : Visited[last].Prevs())
		{
			restPaths = getShortestPaths(start, n, Visited);
			for (auto p : restPaths)
			{
				p.insert(p.begin(), path.begin(), path.end());
				paths.push_back(p);
			}
		}
		return paths;
	}

	vector<vector<int>> Dijkstra(int start, int end, vector<vector<int>> &dists)
	{
		vector<vector<int>> paths;
		auto N = dists.size();
		list<Node> Waiting;
		vector<Node> Visited;
		//Init DijQueue
		Waiting = initWaiting(start, end, dists);
		while (!Waiting.empty())
		{
			Node c = Waiting.front();	//current
			Waiting.pop_front();
			cout << "Id: " << c.Index() << " (Distance: " << c.Dist() << ") Visited" << endl;
			for (auto &n : Waiting)
			{
				int dist = dists[c.Index()][n.Index()];
				if (dist < INFI)
				{
					n.Update(c.Index(), addDist(c.Dist(), dist));
				}
			}
			sortByDist(Waiting);
			Visited.push_back(c);
		}
		sortByIndex(Visited);
		vector<vector<int>> rPaths = getShortestPaths(start, end, Visited);
		for (auto rP : rPaths)
		{
			vector<int> p;
			for (auto rit = rP.rbegin(); rit < rP.rend(); rit++)
			{
				p.push_back(*rit);
			}
			paths.push_back(p);
		}
		return paths;
	}

	vector<vector<string>> Paths2Ladders(vector<vector<int>> paths, vector<string> vec)
	{
		vector<vector<string>> ladders;
		for (auto p : paths)
		{
			vector<string> ladder;
			for (auto n : p)
			{
				ladder.push_back(vec[n]);
			}
			ladders.push_back(ladder);
		}
		return ladders;
	}

public:
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
		dict.insert(start);
		dict.insert(end);
		vector<string> vec = Dict2Vector(dict);
		int intStart, intEnd;

		intStart = getIndex(start, vec);
		intEnd = getIndex(end, vec);
		//TODO:
		//	Reconstitute dists with int[][] instead of vector<vector<int>>
		//	
		//	PS: I swear I will do this.
		vector<vector<int>> dists = Vec2Dists(vec);

		vector<vector<int>> paths = Dijkstra(intStart, intEnd, dists);
		vector<vector<string>> ladders = Paths2Ladders(paths, vec);

		sort(ladders.begin(), ladders.end(),
			[](vector<string> a, vector<string> b){
				auto N = (a.size() <= b.size() ? a.size() : b.size());
				for (decltype(N) i = 0; i < N; ++i)
				{
					if (a[i] == b[i])
					{
						continue;
					}
					else
					{
						return a[i] < b[i];
					}
				}
				return a.size() < b.size();
			}
		);

		return ladders;
	}
};

int main()
{
	string start = "sand";
	string end = "acne";
	unordered_set<string> dict = { "slit", "bunk", "wars", "ping", "viva", "wynn", "wows", "irks", "gang", "pool", "mock", "fort", "heel", "send", "ship", "cols", "alec", "foal", "nabs", "gaze", "giza", "mays", "dogs", "karo", "cums", "jedi", "webb", "lend", "mire", "jose", "catt", "grow", "toss", "magi", "leis", "bead", "kara", "hoof", "than", "ires", "baas", "vein", "kari", "riga", "oars", "gags", "thug", "yawn", "wive", "view", "germ", "flab", "july", "tuck", "rory", "bean", "feed", "rhee", "jeez", "gobs", "lath", "desk", "yoko", "cute", "zeus", "thus", "dims", "link", "dirt", "mara", "disc", "limy", "lewd", "maud", "duly", "elsa", "hart", "rays", "rues", "camp", "lack", "okra", "tome", "math", "plug", "monk", "orly", "friz", "hogs", "yoda", "poop", "tick", "plod", "cloy", "pees", "imps", "lead", "pope", "mall", "frey", "been", "plea", "poll", "male", "teak", "soho", "glob", "bell", "mary", "hail", "scan", "yips", "like", "mull", "kory", "odor", "byte", "kaye", "word", "honk", "asks", "slid", "hopi", "toke", "gore", "flew", "tins", "mown", "oise", "hall", "vega", "sing", "fool", "boat", "bobs", "lain", "soft", "hard", "rots", "sees", "apex", "chan", "told", "woos", "unit", "scow", "gilt", "beef", "jars", "tyre", "imus", "neon", "soap", "dabs", "rein", "ovid", "hose", "husk", "loll", "asia", "cope", "tail", "hazy", "clad", "lash", "sags", "moll", "eddy", "fuel", "lift", "flog", "land", "sigh", "saks", "sail", "hook", "visa", "tier", "maws", "roeg", "gila", "eyes", "noah", "hypo", "tore", "eggs", "rove", "chap", "room", "wait", "lurk", "race", "host", "dada", "lola", "gabs", "sobs", "joel", "keck", "axed", "mead", "gust", "laid", "ends", "oort", "nose", "peer", "kept", "abet", "iran", "mick", "dead", "hags", "tens", "gown", "sick", "odis", "miro", "bill", "fawn", "sumo", "kilt", "huge", "ores", "oran", "flag", "tost", "seth", "sift", "poet", "reds", "pips", "cape", "togo", "wale", "limn", "toll", "ploy", "inns", "snag", "hoes", "jerk", "flux", "fido", "zane", "arab", "gamy", "raze", "lank", "hurt", "rail", "hind", "hoot", "dogy", "away", "pest", "hoed", "pose", "lose", "pole", "alva", "dino", "kind", "clan", "dips", "soup", "veto", "edna", "damp", "gush", "amen", "wits", "pubs", "fuzz", "cash", "pine", "trod", "gunk", "nude", "lost", "rite", "cory", "walt", "mica", "cart", "avow", "wind", "book", "leon", "life", "bang", "draw", "leek", "skis", "dram", "ripe", "mine", "urea", "tiff", "over", "gale", "weir", "defy", "norm", "tull", "whiz", "gill", "ward", "crag", "when", "mill", "firs", "sans", "flue", "reid", "ekes", "jain", "mutt", "hems", "laps", "piss", "pall", "rowe", "prey", "cull", "knew", "size", "wets", "hurl", "wont", "suva", "girt", "prys", "prow", "warn", "naps", "gong", "thru", "livy", "boar", "sade", "amok", "vice", "slat", "emir", "jade", "karl", "loyd", "cerf", "bess", "loss", "rums", "lats", "bode", "subs", "muss", "maim", "kits", "thin", "york", "punt", "gays", "alpo", "aids", "drag", "eras", "mats", "pyre", "clot", "step", "oath", "lout", "wary", "carp", "hums", "tang", "pout", "whip", "fled", "omar", "such", "kano", "jake", "stan", "loop", "fuss", "mini", "byrd", "exit", "fizz", "lire", "emil", "prop", "noes", "awed", "gift", "soli", "sale", "gage", "orin", "slur", "limp", "saar", "arks", "mast", "gnat", "port", "into", "geed", "pave", "awls", "cent", "cunt", "full", "dint", "hank", "mate", "coin", "tars", "scud", "veer", "coax", "bops", "uris", "loom", "shod", "crib", "lids", "drys", "fish", "edit", "dick", "erna", "else", "hahs", "alga", "moho", "wire", "fora", "tums", "ruth", "bets", "duns", "mold", "mush", "swop", "ruby", "bolt", "nave", "kite", "ahem", "brad", "tern", "nips", "whew", "bait", "ooze", "gino", "yuck", "drum", "shoe", "lobe", "dusk", "cult", "paws", "anew", "dado", "nook", "half", "lams", "rich", "cato", "java", "kemp", "vain", "fees", "sham", "auks", "gish", "fire", "elam", "salt", "sour", "loth", "whit", "yogi", "shes", "scam", "yous", "lucy", "inez", "geld", "whig", "thee", "kelp", "loaf", "harm", "tomb", "ever", "airs", "page", "laud", "stun", "paid", "goop", "cobs", "judy", "grab", "doha", "crew", "item", "fogs", "tong", "blip", "vest", "bran", "wend", "bawl", "feel", "jets", "mixt", "tell", "dire", "devi", "milo", "deng", "yews", "weak", "mark", "doug", "fare", "rigs", "poke", "hies", "sian", "suez", "quip", "kens", "lass", "zips", "elva", "brat", "cosy", "teri", "hull", "spun", "russ", "pupa", "weed", "pulp", "main", "grim", "hone", "cord", "barf", "olav", "gaps", "rote", "wilt", "lars", "roll", "balm", "jana", "give", "eire", "faun", "suck", "kegs", "nita", "weer", "tush", "spry", "loge", "nays", "heir", "dope", "roar", "peep", "nags", "ates", "bane", "seas", "sign", "fred", "they", "lien", "kiev", "fops", "said", "lawn", "lind", "miff", "mass", "trig", "sins", "furl", "ruin", "sent", "cray", "maya", "clog", "puns", "silk", "axis", "grog", "jots", "dyer", "mope", "rand", "vend", "keen", "chou", "dose", "rain", "eats", "sped", "maui", "evan", "time", "todd", "skit", "lief", "sops", "outs", "moot", "faze", "biro", "gook", "fill", "oval", "skew", "veil", "born", "slob", "hyde", "twin", "eloy", "beat", "ergs", "sure", "kobe", "eggo", "hens", "jive", "flax", "mons", "dunk", "yest", "begs", "dial", "lodz", "burp", "pile", "much", "dock", "rene", "sago", "racy", "have", "yalu", "glow", "move", "peps", "hods", "kins", "salk", "hand", "cons", "dare", "myra", "sega", "type", "mari", "pelt", "hula", "gulf", "jugs", "flay", "fest", "spat", "toms", "zeno", "taps", "deny", "swag", "afro", "baud", "jabs", "smut", "egos", "lara", "toes", "song", "fray", "luis", "brut", "olen", "mere", "ruff", "slum", "glad", "buds", "silt", "rued", "gelt", "hive", "teem", "ides", "sink", "ands", "wisp", "omen", "lyre", "yuks", "curb", "loam", "darn", "liar", "pugs", "pane", "carl", "sang", "scar", "zeds", "claw", "berg", "hits", "mile", "lite", "khan", "erik", "slug", "loon", "dena", "ruse", "talk", "tusk", "gaol", "tads", "beds", "sock", "howe", "gave", "snob", "ahab", "part", "meir", "jell", "stir", "tels", "spit", "hash", "omit", "jinx", "lyra", "puck", "laue", "beep", "eros", "owed", "cede", "brew", "slue", "mitt", "jest", "lynx", "wads", "gena", "dank", "volt", "gray", "pony", "veld", "bask", "fens", "argo", "work", "taxi", "afar", "boon", "lube", "pass", "lazy", "mist", "blot", "mach", "poky", "rams", "sits", "rend", "dome", "pray", "duck", "hers", "lure", "keep", "gory", "chat", "runt", "jams", "lays", "posy", "bats", "hoff", "rock", "keri", "raul", "yves", "lama", "ramp", "vote", "jody", "pock", "gist", "sass", "iago", "coos", "rank", "lowe", "vows", "koch", "taco", "jinn", "juno", "rape", "band", "aces", "goal", "huck", "lila", "tuft", "swan", "blab", "leda", "gems", "hide", "tack", "porn", "scum", "frat", "plum", "duds", "shad", "arms", "pare", "chin", "gain", "knee", "foot", "line", "dove", "vera", "jays", "fund", "reno", "skid", "boys", "corn", "gwyn", "sash", "weld", "ruiz", "dior", "jess", "leaf", "pars", "cote", "zing", "scat", "nice", "dart", "only", "owls", "hike", "trey", "whys", "ding", "klan", "ross", "barb", "ants", "lean", "dopy", "hock", "tour", "grip", "aldo", "whim", "prom", "rear", "dins", "duff", "dell", "loch", "lava", "sung", "yank", "thar", "curl", "venn", "blow", "pomp", "heat", "trap", "dali", "nets", "seen", "gash", "twig", "dads", "emmy", "rhea", "navy", "haws", "mite", "bows", "alas", "ives", "play", "soon", "doll", "chum", "ajar", "foam", "call", "puke", "kris", "wily", "came", "ales", "reef", "raid", "diet", "prod", "prut", "loot", "soar", "coed", "celt", "seam", "dray", "lump", "jags", "nods", "sole", "kink", "peso", "howl", "cost", "tsar", "uric", "sore", "woes", "sewn", "sake", "cask", "caps", "burl", "tame", "bulk", "neva", "from", "meet", "webs", "spar", "fuck", "buoy", "wept", "west", "dual", "pica", "sold", "seed", "gads", "riff", "neck", "deed", "rudy", "drop", "vale", "flit", "romp", "peak", "jape", "jews", "fain", "dens", "hugo", "elba", "mink", "town", "clam", "feud", "fern", "dung", "newt", "mime", "deem", "inti", "gigs", "sosa", "lope", "lard", "cara", "smug", "lego", "flex", "doth", "paar", "moon", "wren", "tale", "kant", "eels", "muck", "toga", "zens", "lops", "duet", "coil", "gall", "teal", "glib", "muir", "ails", "boer", "them", "rake", "conn", "neat", "frog", "trip", "coma", "must", "mono", "lira", "craw", "sled", "wear", "toby", "reel", "hips", "nate", "pump", "mont", "died", "moss", "lair", "jibe", "oils", "pied", "hobs", "cads", "haze", "muse", "cogs", "figs", "cues", "roes", "whet", "boru", "cozy", "amos", "tans", "news", "hake", "cots", "boas", "tutu", "wavy", "pipe", "typo", "albs", "boom", "dyke", "wail", "woke", "ware", "rita", "fail", "slab", "owes", "jane", "rack", "hell", "lags", "mend", "mask", "hume", "wane", "acne", "team", "holy", "runs", "exes", "dole", "trim", "zola", "trek", "puma", "wacs", "veep", "yaps", "sums", "lush", "tubs", "most", "witt", "bong", "rule", "hear", "awry", "sots", "nils", "bash", "gasp", "inch", "pens", "fies", "juts", "pate", "vine", "zulu", "this", "bare", "veal", "josh", "reek", "ours", "cowl", "club", "farm", "teat", "coat", "dish", "fore", "weft", "exam", "vlad", "floe", "beak", "lane", "ella", "warp", "goth", "ming", "pits", "rent", "tito", "wish", "amps", "says", "hawk", "ways", "punk", "nark", "cagy", "east", "paul", "bose", "solo", "teed", "text", "hews", "snip", "lips", "emit", "orgy", "icon", "tuna", "soul", "kurd", "clod", "calk", "aunt", "bake", "copy", "acid", "duse", "kiln", "spec", "fans", "bani", "irma", "pads", "batu", "logo", "pack", "oder", "atop", "funk", "gide", "bede", "bibs", "taut", "guns", "dana", "puff", "lyme", "flat", "lake", "june", "sets", "gull", "hops", "earn", "clip", "fell", "kama", "seal", "diaz", "cite", "chew", "cuba", "bury", "yard", "bank", "byes", "apia", "cree", "nosh", "judo", "walk", "tape", "taro", "boot", "cods", "lade", "cong", "deft", "slim", "jeri", "rile", "park", "aeon", "fact", "slow", "goff", "cane", "earp", "tart", "does", "acts", "hope", "cant", "buts", "shin", "dude", "ergo", "mode", "gene", "lept", "chen", "beta", "eden", "pang", "saab", "fang", "whir", "cove", "perk", "fads", "rugs", "herb", "putt", "nous", "vane", "corm", "stay", "bids", "vela", "roof", "isms", "sics", "gone", "swum", "wiry", "cram", "rink", "pert", "heap", "sikh", "dais", "cell", "peel", "nuke", "buss", "rasp", "none", "slut", "bent", "dams", "serb", "dork", "bays", "kale", "cora", "wake", "welt", "rind", "trot", "sloe", "pity", "rout", "eves", "fats", "furs", "pogo", "beth", "hued", "edam", "iamb", "glee", "lute", "keel", "airy", "easy", "tire", "rube", "bogy", "sine", "chop", "rood", "elbe", "mike", "garb", "jill", "gaul", "chit", "dons", "bars", "ride", "beck", "toad", "make", "head", "suds", "pike", "snot", "swat", "peed", "same", "gaza", "lent", "gait", "gael", "elks", "hang", "nerf", "rosy", "shut", "glop", "pain", "dion", "deaf", "hero", "doer", "wost", "wage", "wash", "pats", "narc", "ions", "dice", "quay", "vied", "eons", "case", "pour", "urns", "reva", "rags", "aden", "bone", "rang", "aura", "iraq", "toot", "rome", "hals", "megs", "pond", "john", "yeps", "pawl", "warm", "bird", "tint", "jowl", "gibe", "come", "hold", "pail", "wipe", "bike", "rips", "eery", "kent", "hims", "inks", "fink", "mott", "ices", "macy", "serf", "keys", "tarp", "cops", "sods", "feet", "tear", "benz", "buys", "colo", "boil", "sews", "enos", "watt", "pull", "brag", "cork", "save", "mint", "feat", "jamb", "rubs" };
	Solution s;
	vector<vector<string>> ladders = s.findLadders(start, end, dict);
	for (auto l : ladders)
	{
		for (auto str : l)
		{
			cout << str << " ";
		}
		cout << endl;
	}
}