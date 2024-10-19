/** @format */
import angular, { element } from "angular"
import { html } from "@/util"
import { get } from "jquery"

export default angular.module("korpApp").component("filter", {
    template: html`<span class="pl-4">
        Filter:
        <uib-dropdown>
            <button uib-dropdown-toggle type="button">{{$ctrl.selected}}<span class="caret"></span></button>
            <ul uib-dropdown-menu>
                <li ng-repeat="item in $ctrl.types">
                    <a href="" ng-click="$ctrl.selectItem(item)">{{item}}</a>
                </li>
            </ul>
        </uib-dropdown>
    </span>`,
    bindings: {
        search: "<",
        kwicHits: "<",
        onKwicChange: "&",
    },
    controller: [
        "$timeout",
        /**
         * @param {import("angular").ITimeoutService} $timeout
         */
        function ($timeout, $scope) {
            let $ctrl: any = this
            $ctrl.selected = "kõik"
            const kwicHitsByType: Map<string, Map<number, Object>> = new Map()
            const mapOfAll: Map<number, Object> = new Map()

            $ctrl.selectItem = function (item) {
                $ctrl.selected = item
                const newKwic = [...kwicHitsByType.get(item)!.values()]
                $ctrl.onKwicChange({ newKwic: newKwic })
            }

            $ctrl.$onChanges = (changes) => {
                if ($ctrl.search) return
                $ctrl.selected = "kõik"
                $timeout(() => {
                    if ($ctrl.kwicHits === undefined) return
                    for (const [index, kwicHit] of $ctrl.kwicHits.entries()) {
                        mapOfAll.set(index, kwicHit)
                        if (kwicHit.match === undefined) continue
                        kwicHit.tokens.forEach((token) => {
                            if (token.error_type === undefined || token.error_type === "_") return
                            token.error_type.split("|").forEach((type) => {
                                if (kwicHitsByType.has(type)) {
                                    kwicHitsByType.get(type)!.set(index, kwicHit)
                                    return
                                }
                                const map = new Map()
                                map.set(0, mapOfAll.get(0))
                                map.set(index, kwicHit)
                                kwicHitsByType.set(type, map)
                                if (index === 1) {
                                }
                            })
                        })
                    }
                    $ctrl.types = Array.from(kwicHitsByType.keys())
                    kwicHitsByType.set("kõik", mapOfAll)
                }, 1000)
            }
        },
    ],
})
