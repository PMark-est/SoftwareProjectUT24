/// <reference types="angular"/>

class PopupService {
    static $inject = ['$rootScope']

    constructor(private $rootScope: angular.IRootScopeService) {}

    showPopups(data: number): void {
        this.$rootScope.$emit("showPopups", data)
    }

    onShowPopups(scope: angular.IScope, callback: (data: number) => void): void {
        const handler = this.$rootScope.$on("showPopups", (event, data: number) => callback(data))

        scope.$on('$destroy', handler)
    }
}

angular.module('korpApp').service('popupService', PopupService)