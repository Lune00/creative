import {
    Model
} from '@/models/model-helpers.js'

import {
    ModelParameters
} from '@/models/model-parameters.js'

class GeneticSupport {

    constructor(name, nature, nbOfGenes, alleles, rules) {
        this.name = name,
            this.nature = nature,
            this.nbOfGenes = nbOfGenes,
            this.alleles = alleles,
            this.rules = rules
    }
}


const GeneticSupportValidation = {

    isFeatureDiscrete(nature) {
        return ModelParameters.discreteNature() === nature
    },
    isFeatureContinuous(nature) {
        return ModelParameters.continuousNature() === nature
    },

    isNameValid(name) {
        return name.length
    },
    isNatureValid(nature) {
        return this.isFeatureDiscrete(nature) ||
            this.isFeatureContinuous(nature)
    },
    isNbOfEncodingGenesValid(nbOfGenes) {
        return nbOfGenes >= 1 && nbOfGenes <= ModelParameters.maxNumberOfEncodingGenes()
    },
    isAllelesNumberValid(alleles) {
        return alleles.length
    },
    isAllelesValidKeys(alleles) {
        const keys = alleles.map(allele => (allele.key).toString())
        //Check for no empty key
        const result = keys.filter(key => key.length === 0)
        if (result.length) {
            return false
        }
        //Check for unicity
        return (new Set(keys)).size === keys.length
    },
    isAllelesValidValues(alleles) {
        const values = alleles.map(allele => allele.value)
        for (let value of values) {
            if (undefined === value || isNaN(parseInt(value)))
                return false
        }
        return true
    },

    isRulesValidValues(rules) {
        const values = rules.map(rule => rule.value)
        //Check for invalid input type (must be int or float only)
        for (let value of values) {
            if (undefined === value || isNaN(parseFloat(value)))
                return false
        }
        //Check that each rule is between 0 and 1
        for (let value of values) {
            if (value < 0 || value > 1)
                return false
        }

        return true

    },
    isSetOfRulesComplete(rules, alleles) {

        //Lazy check:
        const nbOfRules = rules.length
        if (nbOfRules !== this.expectedNumberOfRules(alleles.length))
            return false

        //Complete check:
        const ids = alleles.map(allele => allele.id)
        for (let i = 0; i !== ids.length; i++) {
            for (let j = i; j !== ids.length; j++) {
                const index_i = ids[i]
                const index_j = ids[j]
                if (!Model.rules.get(rules, index_i, index_j))
                    return false
            }
        }
        return true
    },

    expectedNumberOfRules(nOfAlleles) {
        return nOfAlleles * (nOfAlleles + 1) / 2
    }
}


export {
    GeneticSupport,
    GeneticSupportValidation
}