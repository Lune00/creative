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

      <h2>Codominance Rules</h2>
      <CodominanceRulesTable
        :alleles="alleles"
        :rules="rules"
      ></CodominanceRulesTable>

      <p>
        <input type="submit" value="Save" />
      </p>
    </form>
  </div>
</template>

<script>
import AllelesEditableList from '@/components/Editor/AllelesEditableList.vue'
import CodominanceRulesTable from '@/components/Editor/CodominanceRulesTable.vue'
import { Model, ModelParametersValidation } from '@/models/model-helpers.js'
import { ModelParameters } from '@/models/model-parameters.js'
import { ErrorState } from '@/services/FormValidationService.js'
import Allele from '@/models/Allele.js'

export default {
  name: 'TheFormAddAbstractFeature',
  components: {
    AllelesEditableList,
    CodominanceRulesTable
  },
  data() {
    return {
      name: '',
      nature: '',
      nbOfGenes: 3,
      alleles: [],
      rules: [],
      allele_id: 0,
      errorState: new ErrorState([
        'name',
        'nature',
        'nbOfGenes',
        'rulesCompletness'
      ])
    }
  },
  methods: {
    checkForm: function() {
      this.errorState.clear()
      //Check que l'allele a un nom
      if (!ModelParametersValidation.geneticSupport.isNameValid(this.name))
        this.errorState.addMessage(
          'name',
          'The name of the genetic support is necessary, please fill in'
        )

      //Check nature est continue ou discrete
      if (!ModelParametersValidation.geneticSupport.isNatureValid(this.nature))
        this.errorState.addMessage(
          'nature',
          'The nature of the genetic material needs to be defined either as Discrete or Continuous'
        )

      //Check que nombre de genes est entre 1 et 99
      if (
        !ModelParametersValidation.geneticSupport.isNbOfEncodingGenesValid(
          this.nbOfGenes
        )
      )
        this.errorState.addMessage(
          'nbOfGenes',
          'The number of encoding genes of the genetic material needs to between 1 and 99'
        )

      //Check que les alleles n'ont pas le meme key(label, unique pour l'user)

      //Check la completness des rules (lazy: calcule le nombre, si ça passe pas erreur, si ça passe vrai test)

      if (this.errorState.hasErrors()) {
        console.log('Errors have been found', this.errorState)
        return
      }

      this.onSubmit()
    },
    discreteNature() {
      return ModelParameters.discreteNature()
    },
    continuousNature() {
      return ModelParameters.continuousNature()
    },
    onAddAllele() {
      const id = this.generateUniqueAlleleId()
      const allele = new Allele(id, id)
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
      console.log('Submit valid genetic support')
    }
  }
}
</script>
<style lang="scss" scoped>
.form-error {
  color: red;
}
</style>
