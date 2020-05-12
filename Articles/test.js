function bar() {
  // vous pouvez mettre ici une boucle interminable
  console.log(‘bar’);
}

function foo(bar) {
  console.log(‘foo’);
  bar();
}

foo(bar);
console.log(‘ok’);
