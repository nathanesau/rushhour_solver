// cargo run --jamdir "jams"
use clap::App;
use clap::Arg;

use std::collections::HashMap;
use std::collections::HashSet;
use std::collections::VecDeque;

use std::rc::Rc;

pub struct Puzzle {
    pub grid: Vec<Vec<char>>,
    //pub car_names: HashSet<char>,
    pub car_orientation: HashMap<char, bool>,
    pub car_size: HashMap<char, usize>,
    pub fixed_position: HashMap<char, usize>,
    pub initial_node: Option<State>,
    pub search_count: i32,
}

impl Puzzle {
    pub fn new() -> Puzzle {
        Puzzle {
            grid: vec![vec!['x'; 6]; 6],
            //car_names: HashSet::new(),
            car_orientation: HashMap::new(),
            car_size: HashMap::new(),
            fixed_position: HashMap::new(),
            initial_node: Option::None,
            search_count: 1,
        }
    }
}

pub struct State {    
    pub variable_position: HashMap<char, usize>,
}

impl State {
    pub fn is_goal(&self) -> bool {
        return self.variable_position[&'x'] == 5;
    }

    pub fn get_grid(&self) -> bool {
        // TODO
        return false;
    }

    pub fn expand(&self) -> bool {
        // TODO
        return false;
    }
}

pub struct Node {
    pub state: Rc<State>,
    pub depth: usize,
    pub parent: Option<Rc<Node>>,
}

impl Node {
    pub fn new(state: Rc<State>, depth: usize, parent: Option<Rc<Node>>) -> Node {
        Node {
            state: state.clone(),
            depth: depth,
            parent: Option::None,
        }
    }

    pub fn expand(&self) -> bool {
        // TODO
        return false;
    }
}

pub fn astar_build_path(current: Rc<Node>) -> VecDeque<Rc<State>> {
    let path: VecDeque<Rc<State>> = VecDeque::new();
    let node = Option::Some(current);
    loop {
        match node {
            None => {
                break;
            }
            Some(_) => {
                println!("hello");
                //path.push_front(value.state);
                //node = value.parent;
            }
        }
    }

    return path;
}

pub fn astar_find_node() -> bool {
    // TODO
    return false;
}

pub fn astar_solve(_: &Puzzle, initial_node: &Node) -> Option<Vec<Rc<State>>> {
    let root = Node::new(
        initial_node.state.clone(),
        initial_node.depth,
        initial_node.parent.clone(),
    );
    let mut open: Vec<Rc<Node>> = vec![Rc::new(root)];
    //let closed = vec![];

    while !open.is_empty() {
        open.sort_by(|a, b| {
            if a.depth < b.depth {
                return std::cmp::Ordering::Less;
            } else if a.depth == b.depth {
                return std::cmp::Ordering::Equal;
            } else {
                return std::cmp::Ordering::Greater;
            }
        });

        let current = open.remove(0);
        if current.state.as_ref().is_goal() {
            let _ = astar_build_path(current);
        }

        // TODO
        // closed.append(current)
        // for successor in current.expand()
        // ...
    }

    // did not find a solution
    return Option::None;
}

fn parse_board(s: &String) -> Puzzle {
    let mut puzzle = Puzzle::new();

    for i in 0..6 {
        for j in 0..6 {
            //puzzle.grid[i][j] = '.';
        }
    }

    //let lines = s.split('\n').map(String::from).collect::<Vec<String>>();
    /*for (i, line) in lines.iter().enumerate() {
        let chars: Vec<char> = line.chars().collect();
        for (j, c) in chars.iter().enumerate() {
            puzzle.grid[i][j] = *c;
        }
    }*/

    let mut car_names = HashSet::new();

    for i in 0..6 {
        for j in 0..6 {
            if puzzle.grid[i][j] != '.' {
                car_names.insert(puzzle.grid[i][j]);
            }
        }
    }

    let mut variable_position = HashMap::new();
    for car_name in car_names {
        let mut squares: Vec<(usize, usize)> = vec![];
        for i in 0..6 {
            for j in 0..6 {
                if puzzle.grid[i][j] == car_name {
                    squares.push((i, j));
                }
            }
        }

        let mut orientation = true;
        for s in &squares[1..] {
            if s.1 != squares[0].1 {
                orientation = false;
                break;
            }
        }

        let fp = if orientation {
            squares[0].1
        } else {
            squares[0].0
        };
        let vp = if orientation {
            squares[0].0
        } else {
            squares[0].1
        };

        puzzle.car_orientation.insert(car_name, orientation);
        puzzle.car_size.insert(car_name, squares.len());
        puzzle.fixed_position.insert(car_name, fp);
        variable_position.insert(car_name, vp);
    }

    let _ = State {
        variable_position: variable_position,
    };

    // TODO create initial_node using state
    // TODO set puzzle.initial_node

    return puzzle;
}

fn main() {
    let clap_app = App::new("rushhour_solver").arg(
        Arg::with_name("jamdir")
            .long("jamdir")
            .takes_value(true)
            .default_value("jams")
            .help("specify the directory containg jam files"),
    );

    let matches = clap_app.get_matches();
    let jamdir = matches.value_of("jamdir").unwrap();

    //let board = std::fs::read_to_string(format!("{}/jam_1.txt", jamdir)).expect("file not found!");
    let board = std::fs::read_to_string(format!("jam.txt")).expect("file not found!");
    let puzzle = parse_board(&board);

    // TODO finish code
}
