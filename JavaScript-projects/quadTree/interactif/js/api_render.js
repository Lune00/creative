//API to render using p5
//sketch : p5 template instanciation
const apiP5 = {

  showPoint: function(sketch, point, color) {
    sketch.stroke(color);
    sketch.strokeWeight(3);
    sketch.point(point.x, point.y);
  },

  showParticle: function(sketch, particle, color) {
    sketch.stroke(color);
    sketch.strokeWeight(1);
    sketch.stroke(0);
    sketch.fill(255);
    if (particle.overlap)
      sketch.fill('#33FF57');
    sketch.circle(particle.x, particle.y, 2 * particle.r);
  },

  showCircularProbe: function(sketch, circularProbe) {
    if (sketch.mouseX > 0 && sketch.mouseX < sketch.width && sketch.mouseY > 0 && sketch.mouseY < sketch.height) {
      sketch.stroke('#5733FF');
      sketch.strokeWeight(1.5);
      sketch.noFill();
      sketch.circle(circularProbe.x, circularProbe.y, 2 * circularProbe.r);
    }
  },

  //TODO : refactor later these 2 functions
  showNode: function(sketch, node) {
    sketch.push();
    sketch.rectMode(sketch.CENTER);
    sketch.noFill();
    sketch.stroke(150);
    sketch.strokeWeight(0.5);
    sketch.rect(node.x, node.y, 2 * node.w, 2 * node.h);
    sketch.pop();

    node.children.forEach(child => {
      if (child instanceof Node)
        this.showNode(sketch, child);
      else
        child.forEach(p => this.showPoint(sketch, p, 'white'));
    });
  },

  showNodeAndHighlightIntersectedLeafs: function(sketch, node) {
    sketch.push();
    sketch.rectMode(sketch.CENTER);

    if (node.intersected) {
      sketch.fill(100);
    } else {
      sketch.fill(0);
    }
    sketch.stroke(150);
    sketch.strokeWeight(0.5);
    sketch.rect(node.x, node.y, 2 * node.w, 2 * node.h);
    sketch.pop();

    node.children.forEach(child => {
      if (child instanceof Node)
        this.showNodeAndHighlightIntersectedLeafs(sketch, child);
      else
        child.forEach(p => this.showPoint(sketch, p, 'white'));
    });
  },

  showNodeWithDepth: function(sketch, node) {
    let maxDepth = node.getMaxDepth()
    this.showNodeContent(sketch, node, maxDepth);
  },

  showNodeContent: function(sketch, node, maxDepth) {
    this.showNode(sketch, node, maxDepth);
    node.children.forEach(child => {
      if (child instanceof Node) {
        this.showNodeContent(sketch, child, maxDepth);
      } else
        child.forEach(p => this.showPoint(sketch, p, 'white'));
    });
  },

  showNode: function(sketch, node, maxDepth) {
    sketch.push();
    sketch.rectMode(sketch.CENTER);

    sketch.strokeWeight(0.5);
    sketch.stroke(255);

    let c = sketch.map(node.depth, 0, maxDepth + 1 , 0, 255);
    // console.log(this.depth, maxDepth, c);
    sketch.fill(0,c/2,c);

    sketch.rect(node.x, node.y, 2 * node.w, 2 * node.h);
    sketch.pop();
  }

}
