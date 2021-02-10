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

    //Return Rule(id_i,id_j) if it exists in array rules, false otherwise
    getRule(rules, id_i, id_j) {

    }

}