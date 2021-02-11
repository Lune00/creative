<template lang="">
  <div>
    <h1>Add a new Genetic Support</h1>
    <form
      id="add_abstract_feature"
      @submit.prevent="checkForm"
      action="#"
      method="post"
    >
      <h2>General</h2>

      <div v-if="errorState.hasErrors()">
        Errors have been found, please check again to submit your data
      </div>

      <p>
        <label for="af_label">Name: </label>
        <input type="text" id="af_label" name="af_label" v-model="name" />
      </p>

      <div class="form-error" v-if="errorState.hasError('name')">
        {{ errorState.messages('name').join(',') }}
      </div>

      <p>
        <label for="af_nature">Nature: </label>
        <select v-model="nature" name="af_nature" id="af_nature">
          <option :value="this.discreteNature()">Discrete</option>
          <option :value="this.continuousNature()">Continuous</option>
        </select>
      </p>
      <div class="form-error" v-if="errorState.hasError('nature')">
        {{ errorState.messages('nature').join(',') }}
      </div>

      <p>
        <label for="nb_genes">Number of encoding genes: </label>
        <input
          type="number"
          id="af_nbgenes"
          name="af_nbgenes"
          min="1"
          max="99"
          step="1"
          v-model="nbOfGenes"
        />
      </p>
      <div class="form-error" v-if="errorState.hasError('nbOfGenes')">
        {{ errorState.messages('nbOfGenes').join(',') }}
      </div>

      <h2>Alleles</h2>
      <AllelesEditableList
        :nature="nature"
        :alleles="alleles"
        @add_allele="onAddAllele"
        @remove_allele="onRemoveAllele"
      ></AllelesEditableList>
      <div class="form-error" v-if="errorState.hasError('alleles')">
        {{ errorState.messages('alleles').join(',') }}
      </div>

      <h2>Codominance Rules</h2>
      <div class="documentation">
        <h3>How to read</h3>
        <div>Lore ipsum...</div>
      </div>
      <div v-if="nature === discreteNature()">
        You have choosed a discrete nature for this genetic support. The
        codominance rules are interpreted as probability of expression. For more
        information, please read the <a href="#">documentation</a>
      </div>
      <CodominanceRulesTable
        :alleles="alleles"
        :rules="rules"
      ></CodominanceRulesTable>
      <div class="form-error" v-if="errorState.hasError('rules')">
        {{ errorState.messages('rules').join(',') }}
      </div>

      <p>
        <input type="submit" value="Save" />
      </p>
    </form>
  </div>
</template>

<script>
import AllelesEditableList from '@/components/Editor/AllelesEditableList.vue'
import CodominanceRulesTable from '@/components/Editor/CodominanceRulesTable.vue'
import { Model } from '@/models/model-helpers.js'
import { ModelParameters } from '@/models/model-parameters.js'
import {
  GeneticSupport,
  GeneticSupportValidation
} from '@/models/GeneticSupport.js'
import { ErrorState } from '@/services/FormValidationService.js'
import Allele from '@/models/Allele.js'

import geneticSupportRepository from '@/services/repository/geneticSupportRepository'

export default {
  name: 'TheFormAddAbstractFeature',
  components: {
    AllelesEditableList,
    CodominanceRulesTable
  },
  data() {
    return {
      name: 'Foo',
      nature: ModelParameters.discreteNature(),
      nbOfGenes: 3,
      alleles: [],
      rules: [],
      allele_id: 0,
      errorState: new ErrorState([
        'name',
        'nature',
        'nbOfGenes',
        'alleles',
        'rules'
      ])
    }
  },
  methods: {
    discreteNature() {
      return ModelParameters.discreteNature()
    },
    continuousNature() {
      return ModelParameters.continuousNature()
    },
    onAddAllele() {
      const id = this.generateUniqueAlleleId()
      const allele = new Allele(id, id, 1)
      this.alleles.push(allele)
      this.rules = Model.rules.addAllele(this.rules, this.alleles, allele)
    },
    onRemoveAllele(index) {
      const removedAllele = this.alleles.splice(index, 1)
      this.rules = Model.rules.removeAllele(this.rules, removedAllele)
    },
    generateUniqueAlleleId() {
      const id = this.allele_id
      this.allele_id++
      return id
    },
    onSubmit() {
      const geneticSupport = new GeneticSupport(
        this.name,
        this.nature,
        this.nbOfGenes,
        this.alleles,
        this.rules
      )
      console.log('Submit valid genetic support', geneticSupport)

      geneticSupportRepository.get().then(result => {
        console.log(result)
      })
    },
    checkForm: function() {
      this.errorState.clear()
      //Check que l'allele a un nom
      if (!GeneticSupportValidation.isNameValid(this.name))
        this.errorState.addMessage(
          'name',
          'The name of the genetic support is necessary, please fill in'
        )

      //Check nature est continue ou discrete
      if (!GeneticSupportValidation.isNatureValid(this.nature))
        this.errorState.addMessage(
          'nature',
          'The nature of the genetic material needs to be defined either as Discrete or Continuous'
        )

      //Check que nombre de genes est entre 1 et 99
      if (!GeneticSupportValidation.isNbOfEncodingGenesValid(this.nbOfGenes))
        this.errorState.addMessage(
          'nbOfGenes',
          'The number of encoding genes of the genetic material needs to between 1 and 99'
        )

      //Check que y'a un moins une allele
      if (!GeneticSupportValidation.isAllelesNumberValid(this.alleles))
        this.errorState.addMessage(
          'alleles',
          'You should have at least one allele for the genetic support'
        )

      //Check que les alleles n'ont pas le meme key(label, unique pour l'user)
      if (!GeneticSupportValidation.isAllelesValidKeys(this.alleles))
        this.errorState.addMessage(
          'alleles',
          'The alleles must have a unique label'
        )

      //Check que les alleles ont toutes une value
      if (!GeneticSupportValidation.isAllelesValidValues(this.alleles))
        this.errorState.addMessage('alleles', 'The alleles must have a value')

      //Check que chaque regle a une valeur, comprise entre 0 et 1
      if (!GeneticSupportValidation.isRulesValidValues(this.rules))
        this.errorState.addMessage(
          'rules',
          'Some rules are not valid, each rule should have a value between 0 and 1 included'
        )

      //Check la completness des rules (lazy: calcule le nombre, si ça passe pas erreur, si ça passe vrai test)
      if (
        !GeneticSupportValidation.isSetOfRulesComplete(this.rules, this.alleles)
      )
        this.errorState.addMessage(
          'rules',
          'The set of rules is not complete and do not cover all possible alleles combinations, please correct it'
        )

      if (this.errorState.hasErrors()) return

      this.onSubmit()
    }
  }
}
</script>
<style lang="scss" scoped>
.form-error {
  color: red;
}
</style>
