class Rule {

    constructor(id_a, id_b, value) {

        let temp
        if (id_a > id_b) {
            temp = id_a
            id_a = id_b
            id_b = temp
        }

        this.id_a = id_a
        this.id_b = id_b

        this.value = value
    }

    equalsTo(rule) {
        if (!(rule instanceof Rule))
            return false
        return this.id_a == rule.id_a && this.id_b == this.id_b
    }

}

export default Rule