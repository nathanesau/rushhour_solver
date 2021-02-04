use clap::App;
use clap::Arg;

use std::collections::HashMap;
use std::rc::Rc;
use std::cell::RefCell;
use std::collections::VecDeque;

pub struct Puzzle {
    // ideally, we would use HashSet
    // however, HashSet cannot be easily be moved
    pub car_names: Vec<char>,
    pub car_orientation: HashMap<char, bool>,
    pub car_size: HashMap<char, usize>,
    pub fixed_position: HashMap<char, usize>,
    pub search_count: i32,
}

impl Puzzle {
    pub fn new() -> Puzzle {
        Puzzle {
            car_names: vec![],
            car_orientation: HashMap::new(),
            car_size: HashMap::new(),
            fixed_position: HashMap::new(),
            search_count: 1,
        }
    }
}

pub struct State<'a> {
    pub puzzle: &'a Puzzle,

    pub variable_position: HashMap<char, usize>,
}

impl<'a> State<'a> {
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

pub struct Node<'a> {
    pub state: State<'a>,
    pub depth: usize,
    pub parent: Option<Rc<Node<'a>>>,
}

fn parse_board(s: &String) -> (Puzzle, HashMap<char, usize>) {

    let mut puzzle = Puzzle::new();

    let mut grid: [[char; 6]; 6] = [['.'; 6]; 6];

    let lines = s.split('\n').map(String::from).collect::<Vec<String>>();
    for (i, line) in lines.iter().enumerate() {
        if i >= 6 {
            break;
        }
        let chars: Vec<char> = line.chars().collect();
        for (j, c) in chars.iter().enumerate() {
            if j >= 6 {
                break;
            }
            grid[i][j] = *c;
        }
    }

    for i in 0..6 {
        for j in 0..6 {
            if grid[i][j] != '.' && !puzzle.car_names.contains(&grid[i][j]) {
                puzzle.car_names.push(grid[i][j]);
            }
        }
    }

    let mut variable_position = HashMap::new();
    for car_name in &puzzle.car_names {
        let mut squares: Vec<(usize, usize)> = vec![];
        for i in 0..6 {
            for j in 0..6 {
                if grid[i][j] == *car_name {
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

        puzzle.car_orientation.insert(*car_name, orientation);
        puzzle.car_size.insert(*car_name, squares.len());
        puzzle.fixed_position.insert(*car_name, fp);
        variable_position.insert(*car_name, vp);
    }

    return (puzzle, variable_position);
}

pub fn astar_build_path<'a>(current: Rc<RefCell<Node>>) -> VecDeque<State<'a>> {
    let path: VecDeque<State> = VecDeque::new();
    let node = Option::Some(current);
    loop {
        match node {
            None => {
                break;
            }
            Some(_) => {
                // TODO push nodes
            }
        }
    }

    return path;
}

// NOTE: initial_node is moved into the function
pub fn astar_solve<'a>(puzzle: &Puzzle, initial_node: Node) -> Option<VecDeque<State<'a>>> {
    // NOTE: initial_node is copied into root node
    let root: Rc<RefCell<Node>> = Rc::new(RefCell::new(Node {
        state: State {
            puzzle: initial_node.state.puzzle,
            variable_position: initial_node.state.variable_position
        },
        depth: initial_node.depth,
        parent: initial_node.parent
    }));
    // start with root node
    let mut open: Vec<Rc<RefCell<Node>>> = vec![root.clone()];
    let mut closed: Vec<Rc<RefCell<Node>>> = vec![];
    // copy node
    let mut nodes = vec![];
    nodes.push(root);
    
    while !open.is_empty() {
        open.sort_by(|a, b| {
            if a.borrow().depth < b.borrow().depth {
                return std::cmp::Ordering::Less;
            } else if a.borrow().depth == b.borrow().depth {
                return std::cmp::Ordering::Equal;
            } else {
                return std::cmp::Ordering::Greater;
            }
        });

        // clone here because we erase the shared ptr from open afterwards
        let current = open[0].clone();
        open.remove(0);

        if current.borrow().state.is_goal() {
            let path = astar_build_path(current);
            return Some(path);
        }

        // no harm in cloning here
        closed.push(current.clone());

        // TODO get expanded nodes
        let new_nodes: Vec<Rc<RefCell<Node>>> = vec![];

        for successor in new_nodes {
            nodes.push(successor);
            // TODO check if node is found, etc.
        }
    }

    return Option::None;
}

pub fn main() {
    let clap_app = App::new("rushhour_solver").arg(
        Arg::with_name("jamdir")
            .long("jamdir")
            .takes_value(true)
            .default_value("jams")
            .help("specify the directory containg jam files"),
    );

    let matches = clap_app.get_matches();
    let jamdir = matches.value_of("jamdir").unwrap();

    let board = std::fs::read_to_string(format!("{}/jam_1.txt", jamdir))
        .expect("jam file was not found in provided jamdir!");

    let info = parse_board(&board);
    let puzzle = info.0;
    let variable_position = info.1;

    let initial_node = Node {
        state: State {
            puzzle: &puzzle,
            variable_position: variable_position
        },
        depth: 0,
        parent: Option::None
    };

    let path = astar_solve(&puzzle, initial_node);

    println!("solve finished!");
}
