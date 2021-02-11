import Rule from '@/models/Rule.js'
// import Allele from '@/models/Allele.js'

export default {
    discreteNature() {
        return 'discrete'
    },
    continuousNature() {
        return 'continuous'
    },
    isFeatureDiscrete(nature) {
        return 'discrete' === nature
    },
    isFeatureContinuous(nature) {
        return 'continuous' === nature
    },

    //Return Rule(id_i,id_j) if it exists in array rules, undefined otherwise
    getRule(rules, id_i, id_j) {

        let temp

        if (id_i > id_j) {
            temp = id_i
            id_i = id_j
            id_j = temp
        }
        return rules.find(rule => {
            return parseInt(id_i) === parseInt(rule.id_a) && parseInt(id_j) === parseInt(rule.id_b)
        })

    },


    getRuleValue(rules, id_i, id_j) {
        const rule = this.getRule(rules, id_i, id_j)
        const value = rule.value
        if (id_i > id_j)
            return 1. - value

        return value
    },

    rules_add_allele(rules, alleles, new_allele) {

        const id = new_allele.id
        const defaultRuleValue = 0.3

        const new_rules = new Array()

        alleles.forEach(allele => {

            const target_allele_id = allele.id
            const rule = this.getRule(rules, target_allele_id, id)

            if (!rule) {
                new_rules.push(new Rule(target_allele_id, id, defaultRuleValue))
            }
        })
        return rules.concat(new_rules)
    },

    rules_remove_allele(rules, removed_alleles) {
        const ids = removed_alleles.map(allele => parseInt(allele.id))
        const rules_to_remove = this.filterAssociatedRules(rules, ids)
        const new_rules = rules.filter(rule => {
            return rules_to_remove.indexOf(rule) < 0
        })
        return new_rules
    },

    //Return rules that applied to an array of Allele ids
    filterAssociatedRules(rules, ids) {
        return rules.filter(rule => {
            return this.isRuleAssociatedTo(rule, ids)
        })
    },

    //Return true if rule applied to one of Allele id in ids
    isRuleAssociatedTo(rule, ids) {
        for (const id of ids) {
            if (rule.applyToAllele(id)) {
                return true
            }
        }
        return false
    }
}