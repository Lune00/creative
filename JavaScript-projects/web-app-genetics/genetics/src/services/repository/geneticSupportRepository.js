import {
    Repository
} from './index'

export default {
    get() {
        return Repository.get('/geneticSupport')
    }
}