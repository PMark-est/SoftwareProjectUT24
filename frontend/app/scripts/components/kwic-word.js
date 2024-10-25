/** @format */
import angular from "angular"
import { html } from "@/util"

angular.module("korpApp").component("kwicWord", {
    template: html`<span class="word" ng-class="$ctrl.getClass()"> {{::$ctrl.word.word}} </span> `,
    bindings: {
        word: "<",
        sentence: "<",
        sentenceIndex: "<",
    },
    controller: [
        "$scope",
        function ($scope) {
            this.$onInit = () => {
                // Add incoming values to local scope, to be used by click handlers in the Kwic component.
                $scope.word = this.word
                $scope.sentence = this.sentence
                $scope.sentenceIndex = this.sentenceIndex
            }

            /** Produce applicable class names depending on token data. */
            this.getClass = function () {
                let errorType = ["_"]
                if (this.word.error_type) {
                    errorType = this.word.error_type.split("|")
                }
                let classes = []
                classes.push({
                    reading_match: this.word._match,
                    punct: this.word._punct,
                    match_sentence: this.word._matchSentence,
                    link_selected: this.word._link_selected,
                    open_sentence: "_open_sentence" in this.word,
                    has_error: this.word.error_tag && this.word.error_tag != "_",
                })
                classes = classes.concat(errorType)
                //console.log(classes)
                return classes
            }
        },
    ],
})