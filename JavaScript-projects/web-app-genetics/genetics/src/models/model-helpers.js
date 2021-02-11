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
            id_i === rule.id_a && id_j === rule.id_b
        })
    },

    rules_add_allele(rules, alleles, new_allele) {

        const id = new_allele.id
        const defaultRuleValue = 0

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

    //Return rules that concern array of Allele ids
    filterAssociatedRules(rules, ids) {
        return rules.filter(rule => {
            return this.filterAssociatedRule(rule, ids)
        })
    },

    //Return true if the rule is concerned by an Allele id
    filterAssociatedRule(rule, ids) {
        for (const id of ids) {
            if (rule.applyToAllele(id)) {
                return true
            }
        }
        return false
    }
}