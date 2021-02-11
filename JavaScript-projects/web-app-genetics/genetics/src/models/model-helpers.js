import Rule from '@/models/Rule.js'
import {
  ModelParameters
} from '@/models/model-parameters.js'

const Model = {
  nature: {

  },

  rules: {
    //Return Rule from rules associated to the arrangement (id_i, id_j), undefined otherwise
    get(rules, id_i, id_j) {
      let temp

      if (id_i > id_j) {
        temp = id_i
        id_i = id_j
        id_j = temp
      }
      return rules.find(rule => {
        return (
          parseInt(id_i) === parseInt(rule.id_a) &&
          parseInt(id_j) === parseInt(rule.id_b)
        )
      })
    },

    getValue(rules, id_i, id_j) {
      const rule = this.get(rules, id_i, id_j)
      const value = rule.value
      if (id_i > id_j) return 1 - value

      return value
    },

    addAllele(rules, alleles, new_allele) {
      const id = new_allele.id
      const defaultRuleValue = ModelParameters.defaultCodominanceRuleValue()
      const new_rules = new Array()

      alleles.forEach(allele => {
        const target_allele_id = allele.id
        const rule = this.get(rules, target_allele_id, id)

        if (!rule) {
          new_rules.push(new Rule(target_allele_id, id, defaultRuleValue))
        }
      })
      return rules.concat(new_rules)
    },

    removeAllele(rules, removed_alleles) {
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
    },

    // rules_check_completness(rules, alleles) {

    // }
  },
}

const ModelParametersValidation = {


  isFeatureDiscrete(nature) {
    return ModelParameters.discreteNature() === nature
  },
  isFeatureContinuous(nature) {
    return ModelParameters.continuousNature() === nature
  },

  geneticSupport: {

    isNameValid(name) {
      return name.length
    },
    isNatureValid(nature) {
      return ModelParametersValidation.isFeatureDiscrete(nature) ||
        ModelParametersValidation.isFeatureContinuous(nature)
    },
    isNbOfEncodingGenesValid(nbOfGenes) {
      return nbOfGenes >= 1 && nbOfGenes <= ModelParameters.maxNumberOfEncodingGenes()
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



}


export {
  Model,
  ModelParametersValidation
}