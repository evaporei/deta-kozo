#[derive(Debug)]
struct Node<T> {
    val: T,
    next: Option<Box<Node<T>>>,
}

impl<T> Node<T> {
    fn new(val: T) -> Self {
        Self { val, next: None }
    }

    fn inner(self) -> T {
        self.val
    }
}

#[derive(Debug)]
struct LinkedList<T> {
    size: usize,
    head: Option<Box<Node<T>>>,
}

impl<T> LinkedList<T> {
    fn new() -> Self {
        Self { head: None, size: 0 }
    }

    fn push_back(&mut self, val: T) {
        self.size += 1;

        let mut new_node = Box::new(Node::new(val));
        new_node.next = self.head.take();
        self.head = Some(new_node);
    }

    fn pop_back(&mut self) -> Option<T> {
        self.head.take().map(|mut node| {
            self.size -= 1; // only if node is Some

            self.head = node.next.take();
            node.inner()
        })
    }
}

fn main() {
    let mut list = LinkedList::new();

    assert_eq!(list.pop_back(), None);
    assert_eq!(list.pop_back(), None);

    list.push_back(3);
    list.push_back(0);
    list.push_back(1);

    assert_eq!(list.pop_back(), Some(1));
    assert_eq!(list.pop_back(), Some(0));
    assert_eq!(list.pop_back(), Some(3));

    assert_eq!(list.pop_back(), None);
}
